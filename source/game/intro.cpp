#include "views/intro.hpp"

#include "engine/inputs.hpp"
#include "utilities/logger.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger()

void intro::initialize()
{
    animationManagerPtr = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");

    idleAnimation = animationManagerPtr->getChild<graphics::animation>("standing");
    walkingAnimation = animationManagerPtr->getChild<graphics::animation>("walking");

    idleAnimation->setSpritesSize(200, 200);
    walkingAnimation->setSpritesSize(200, 200);

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        playerPtr = new engine::entity("Player")
    );

    playerPtr->setCurrentAnimation(idleAnimation);
    playerPtr->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);

    playerPtr->getCoordinates()->setX(0);
    playerPtr->getCoordinates()->setY(getWindowHeight());

    keyboardHandlerPtr = getRoot()->getChild<engine::keyboardHandler>("Keyboard Handler");
}

void intro::setup()
{
    SDL_SetRenderDrawColor(getRenderer(), 255,255,255,255);
    SDL_RenderClear(getRenderer());
}

void intro::update(size_t delta)
{
    float speed = .15;
    int floor = getWindowHeight() - playerPtr->getCurrentAnimation()->getCurrentFrame()->getSprite()->getHeight();
    int wall = getWindowWidth() - playerPtr->getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth();
    playerPtr->setConstraints(0, wall, floor, 0);

    static float verticalVelocity = 0;

    static size_t counter = 0;
    counter += delta;
    bool shouldMove = counter > 16;
    if (shouldMove) counter = 0;

    static float speedBuffer = .0;
    static float verticalSpeedBuffer = .0;

    if (keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::left))
    {
        playerPtr->setCurrentAnimation(walkingAnimation);
        speedBuffer += speed;

        if (shouldMove)
        {
            playerPtr->getCoordinates()->moveHorizontally(-speedBuffer * delta);
            speedBuffer = .0;
        }
        playerPtr->getCurrentAnimation()->flipSprites(graphics::sprite::flip::none);
    }
    if (keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::right))
    {
        playerPtr->setCurrentAnimation(walkingAnimation);
        speedBuffer += speed;

        if (shouldMove)
        {
            playerPtr->getCoordinates()->moveHorizontally(speedBuffer * delta);
            speedBuffer = .0;
        }
        playerPtr->getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);
    }
    if (keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::space) && playerPtr->getCoordinates()->getY() == floor)
    {
        verticalVelocity = 10.;
    }

    verticalSpeedBuffer += verticalVelocity;

    if (shouldMove)
    {
        playerPtr->getCoordinates()->moveVertically(-verticalVelocity *delta);
        verticalSpeedBuffer = .0;
    }

    if (playerPtr->getCoordinates()->getY() < floor)
    {
        verticalVelocity -= .005;
    }

    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::q))
        shouldClose(true);

    playerPtr->playAnimation(delta);
}