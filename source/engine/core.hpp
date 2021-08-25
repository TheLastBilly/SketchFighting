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

#define SDL_IMAGE_DEFAULT_FLAGS (IMG_INIT_JPG | IMG_INIT_PNG)
#define SDL_DEFAULT_FLAGS SDL_INIT_VIDEO
#define SDL_DEFAULT_WINDOW_FLAGS 0
#define SDL_DEFAULT_RENDERER_FLAGS SDL_RENDERER_ACCELERATED

namespace engine
{
    class core: public engine::node
    {
    public:
        register_exception(sdl_initialization_error, "cannot initialize SDL");
        register_exception(sdl_window_creation_error, "cannot create sdl window");
        register_exception(sdl_renderer_creation_error, "cannot create sdl renderer");
        register_exception(active_view_missing_error, "no active view has been specified");

    public:
        core(int width = 800, int height = 600);
        ~core();

    public:
        inline void setAssetsRootPath(const std::string &path)
        { assetsRootPath = path; }
        inline std::string getAssetsRootPath() const
        { return assetsRootPath; }

        inline engine::assetsManager* getAssetsManager() const
        { return assetsManagerPtr.get(); }
        inline engine::viewsManager* getViewsManager() const
        { return viewsManagerPtr.get(); }

        inline void setAppName(const std::string &name)
        { appName = name; }
        inline std::string getAppName() const
        { return appName; }

    protected:
        void initialize();
        void execute();
        void terminate();

    private:
        bool isInitialized() const;
        bool windowShouldClose(const SDL_Event &event) const;
    
    private:
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;

        int width, height;

        graphics::view *currentView = nullptr;

        bool initialized = false;
    
    private:
        std::shared_ptr<engine::assetsManager> assetsManagerPtr;
        std::shared_ptr<engine::viewsManager>  viewsManagerPtr;

        std::string appName = "";

        std::string assetsRootPath = "";
    };

    class _coreLauncher: public core
    {
    public: 
        _coreLauncher(int width = 800, int height = 600): core(width, height) {}

        inline void initialize()
        { this->core::initialize(); }
        inline void execute()
        { this->core::execute(); }
        inline void terminate()
        { this->core::terminate(); }
    };
}

void setupCore(engine::core* gameCore);

#endif