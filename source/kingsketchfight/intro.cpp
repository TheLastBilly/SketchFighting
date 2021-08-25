#include "kingsketchfight/views/intro.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

void intro::setup()
{
    introSprite = getAssetsManager()->getChild<sprite>("Test");
    introAnimation = getAnimationsManager()->getChild<animation>("IntroAnimation");
}

void intro::update(const SDL_Event &event, size_t delta)
{
    // introSprite->render(0,0);
    // renderSpriteOnCenter(introSprite);
    // SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);
    introAnimation->play(delta, 0, 0);
}