#include "graphics/sprite.hpp"

using namespace graphics;

sprite::sprite(const std::string &name, const std::string &path, SDL_Renderer * renderer): 
    node(name), 
    path(path),
    renderer(renderer)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == NULL)
        throw_exception_with_msg(texture_loading_error, IMG_GetError());
    
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if(texture == NULL || SDL_QueryTexture(texture, NULL, NULL, &width, &height) != 0)
        throw_exception_with_msg(texture_loading_error, SDL_GetError());
}

void sprite::render(int x, int y) const
{
    SDL_Rect source, destination;

    source.h = height;
    source.w = width;
    destination = source;

    source.x = source.y = 0;
    source.x = x;
    source.y = y;

    if(SDL_RenderCopy((SDL_Renderer *)renderer, texture, &source, &destination) != 0)
        throw_exception_with_msg(sprite_rendering_error, SDL_GetError());
}