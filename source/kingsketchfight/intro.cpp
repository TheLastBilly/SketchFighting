#include "kingsketchfight/views/intro.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

void intro::setup()
{
    introSprite = getAssetsManager()->getChild<sprite>("Test");
    introAnimation = getAnimationsManager()->getChild<animation>("IntroAnimation");

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        playerPtr = new engine::player("Player")
    );
    playerPtr->setCurrentAnimation(introAnimation);
}

void intro::update(const SDL_Event &event, size_t delta)
{
    // introSprite->render(0,0);
    // renderSpriteOnCenter(introSprite);
    // SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
    playerPtr->playAnimation(delta);
}