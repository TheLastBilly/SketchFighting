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
        enum flip
        {
            horizontal = SDL_FLIP_HORIZONTAL ,
            vertical = SDL_FLIP_VERTICAL,
            none = SDL_FLIP_NONE
        };

    public:
        sprite(const std::string &name, const std::string &path, SDL_Renderer * renderer);
        ~sprite()
        {
            if(texture != NULL)
                SDL_DestroyTexture(texture);
        }

        void render(int x, int y) const;

        inline int getWidth() const
        { return width; }
        inline int getHeight() const
        { return height; }

        inline int getDefaultWidth() const
        { return defaultWidth; }
        inline int getDefaultHeight() const
        { return defaultHeight; }

        inline void setWidth(int width)
        { this->width = width; }
        inline void setHeight(int height)
        { this->height = height; }

        inline void setFlip(flip f)
        { currentFlip = static_cast<SDL_RendererFlip>(f); }

    private:
        SDL_Texture* texture = NULL;
        const std::string path;
        const SDL_Renderer* renderer;

        SDL_RendererFlip currentFlip = SDL_FLIP_NONE;

        int width = 0, height = 0, defaultWidth = 0, defaultHeight = 0;
    };
}