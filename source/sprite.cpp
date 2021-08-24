#include "graphics/sprite.hpp"

using namespace graphics;

sprite::sprite(const std::string &name, const std::string &path): node(name)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
}