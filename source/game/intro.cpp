#include "views/intro.hpp"

#include "engine/inputs.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger();

void intro::initialize()
{
    introSprite = getRoot()->getChild<managers::assetsManager>("Assets Manager")->getChild<sprite>("Test");
    introAnimation = getRoot()->getChild<managers::animationsManager>("Animations Manager")->getChild<animation>("IntroAnimation");
    introAnimation->setRepeat(false);

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        playerPtr = new engine::entity("Player")
    );
    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        enemyPtr = new engine::entity("Enemy")
    );

    playerPtr->setCurrentAnimation(introAnimation);
    playerPtr->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);

    enemyPtr->setCurrentAnimation(introAnimation);
    enemyPtr->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);

    enemyPtr->getCoordinates()->setX(400);
    enemyPtr->getCoordinates()->setY(300);

    for(size_t i = 0; i < playerPtr->getCurrentAnimation()->getFrameCount(); i++)
    {
        playerPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setHeight(100);
        playerPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setWidth(200);

        enemyPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setHeight(100);
        enemyPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setWidth(200);
    }

    getRoot()->getChild<engine::managers::collisionsManager>("Collisions Manager")->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Entities Collide", playerPtr, enemyPtr,
            [this](engine::entity *a, engine::entity *b)
            { info("Collision detected!"); }
        )
    );

    keyboardHandlerPtr = getRoot()->getChild<engine::keyboardHandler>("Keyboard Handler");
}

void intro::setup()
{
    playerPtr->getCurrentAnimation()->reset();
    
    getRoot()->getChild<engine::managers::collisionsManager>("Collisions Manager")->getCollision("Entities Collide")->setActive(true);
}

void intro::update(size_t delta)
{
    const int speed = 1;

    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::left))
        playerPtr->getCoordinates()->moveHorizontally(-speed*delta);
    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::right))
        playerPtr->getCoordinates()->moveHorizontally(speed*delta);
        
    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::up))
        playerPtr->getCoordinates()->moveVertically(-speed*delta);
    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::down))
        playerPtr->getCoordinates()->moveVertically(speed*delta);

    if(keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::q))
        shouldClose(true);

    playerPtr->playAnimation(delta);
    enemyPtr->playAnimation(delta);

    if(playerPtr->getCurrentAnimation()->isDonePlaying())
    {
        info("Done playing animation \"" + playerPtr->getCurrentAnimation()->getName() + "\"");
        info("Reseting...");
        playerPtr->getCurrentAnimation()->reset();
    }
}