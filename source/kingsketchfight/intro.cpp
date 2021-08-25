#include "kingsketchfight/views/intro.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger();

void intro::initialize()
{
    introSprite = getAssetsManager()->getChild<sprite>("Test");
    introAnimation = getAnimationsManager()->getChild<animation>("IntroAnimation");
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

}

void intro::setup()
{
    playerPtr->getCurrentAnimation()->reset();
}

void intro::update(const SDL_Event &event, size_t delta)
{
    const int speed = 1;

    if(event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            playerPtr->getCoordinates()->moveHorizontally(-speed*delta);
            break;
        case SDLK_RIGHT:
            playerPtr->getCoordinates()->moveHorizontally(speed*delta);
            break;
        case SDLK_UP:
            playerPtr->getCoordinates()->moveVertically(-speed*delta);
            break;
        case SDLK_DOWN:
            playerPtr->getCoordinates()->moveVertically(speed*delta);
            break;
        case SDLK_q:
            shouldClose(true);
            break;
        
        default:
            break;
        }
    }

    playerPtr->playAnimation(delta);
    enemyPtr->playAnimation(delta);

    if(math::collisions::hitboxesCollide(*playerPtr->getHitbox(), *enemyPtr->getHitbox()))
        info("Collision detected!");

    if(playerPtr->getCurrentAnimation()->isDonePlaying())
    {
        info("Done playing animation \"" + playerPtr->getCurrentAnimation()->getName() + "\"");
        info("Reseting...");
        playerPtr->getCurrentAnimation()->reset();
    }
}