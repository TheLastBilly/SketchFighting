#ifndef core_hpp__
#define core_hpp__

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics/view.hpp"
#include "engine/assetsManager.hpp"
#include "engine/viewsManager.hpp"

#include "utilities/exceptions.hpp"
#include "utilities/generics.hpp"

#define SDL_WINDOW_NAME APP_NAME

#define SDL_IMAGE_DEFAULT_FLAGS (IMG_INIT_JPG | IMG_INIT_PNG)
#define SDL_DEFAULT_FLAGS SDL_INIT_VIDEO
#define SDL_DEFAULT_WINDOW_FLAGS 0
#define SDL_DEFAULT_RENDERER_FLAGS SDL_RENDERER_ACCELERATED

namespace graphics
{
    class core: public engine::node
    {
    public:
        register_exception(sdl_initialization_error, "cannot initialize SDL");
        register_exception(sdl_window_creation_error, "cannot create sdl window");
        register_exception(sdl_renderer_creation_error, "cannot create sdl renderer");

    public:
        core(int width, int height);
        ~core();

        void initialize();
        void execute();
        void terminate();

        bool isInitialized() const;

        bool windowShouldClose(const SDL_Event &event) const;
    
    private:
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        int width, height;

        view *currentView, *nextView;

        bool initialized = false;
    
    private:
        std::shared_ptr<engine::assetsManager> assetsManagerPtr;
        std::shared_ptr<engine::viewsManager>  viewsManagerPtr;
    };
}

#endif