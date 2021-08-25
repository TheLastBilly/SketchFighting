#include "kingsketchfight/views/intro.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

void intro::initialize()
{
    introSprite = getAssetsManager()->getChild<sprite>("Test");
    introAnimation = getAnimationsManager()->getChild<animation>("IntroAnimation");

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        playerPtr = new engine::player("Player")
    );

    playerPtr->setCurrentAnimation(introAnimation);
    playerPtr->getCoordinates()->setHorizontalRange(0, getWindowWidth());
    playerPtr->getCoordinates()->setVerticalRange(getWindowHeight(), 0);

    for(size_t i = 0; i < playerPtr->getCurrentAnimation()->getFrameCount(); i++)
    {
        playerPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setHeight(100);
        playerPtr->getCurrentAnimation()->getFrame(i)->getSprite()->setWidth(200);
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
}