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

    public:
        sprite(const std::string &name, const std::string &path);

        void render(SDL_Renderer *render, int x, int y) const;

        int get_width() const
        {
            return width;
        }
        int get_height() const
        {
            return height;
        }

    private:
        SDL_Texture* texture = NULL;
        std::string path;

        int width = 0, height = 0;
    };
}