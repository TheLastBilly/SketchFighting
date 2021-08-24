#ifndef core_hpp__
#define core_hpp__

#include <memory>

#include <SDL2/SDL.h>

#include "graphics/view.hpp"
#include "utilities/exceptions.hpp"
#include "utilities/utilities.hpp"

#define SDL_WINDOW_NAME "Gutless"

#define SDL_DEFAULT_FLAGS SDL_INIT_VIDEO
#define SDL_DEFAULT_WINDOW_FLAGS 0
#define SDL_DEFAULT_RENDERER_FLAGS SDL_RENDERER_ACCELERATED

namespace graphics
{
    class core
    {
    public:
        register_exception(sdl_initialization_error, "cannot initialize SDL");
        register_exception(sdl_window_creation_error, "cannot create sdl window");
        register_exception(sdl_renderer_creation_error, "cannot create sdl renderer");

    public:
        core(int width, int height, const std::shared_ptr<view> &current_view): width(width), height(height), current_view(current_view) {}
        ~core();

        void initialize();
        void execute();
        void terminate();

        bool is_initialized() const;

        bool window_should_close(const SDL_Event &event) const;
    
    private:
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        int width, height;

        std::shared_ptr<view> current_view = nullptr, next_view = nullptr;

        bool initialized = false;
    };
}

#endif