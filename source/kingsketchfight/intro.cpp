#include "kingsketchfight/views/intro.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

void intro::setup()
{
    introSprite = getAssetsManager()->getChild<sprite>("Test");
}

void intro::update(const SDL_Event &event, size_t delta)
{
    introSprite->render(0, 0);
}