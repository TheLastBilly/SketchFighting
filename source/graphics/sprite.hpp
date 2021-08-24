#pragma once

#include "engine/node.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace graphics
{
    class sprite: public engine::node
    {
    public:
        register_exception(texture_loading_error, "cannot load specified texture");
        register_exception(sprite_rendering_error, "cannot render current sprite");

    public:
        sprite(const std::string &name, const std::string &path, SDL_Renderer * renderer);
        ~sprite()
        {
            if(texture != NULL)
                SDL_DestroyTexture(texture);
        }

        void render(int x, int y) const;

        int getWidth() const
        {
            return width;
        }
        int getHeight() const
        {
            return height;
        }

    private:
        SDL_Texture* texture = NULL;
        const std::string path;
        const SDL_Renderer* renderer;

        int width = 0, height = 0;
    };
}