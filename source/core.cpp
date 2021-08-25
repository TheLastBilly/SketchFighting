#include "engine/core.hpp"
#include "utilities/logger.hpp"

register_logger();

using namespace graphics;
using namespace engine;

core::core(int width, int height):
    node("Root"),

    width(width), 
    height(height), 
    currentView(currentView),

    assetsManagerPtr(std::make_shared<assetsManager>("Assets Manager")),
    viewsManagerPtr(std::make_shared<viewsManager>("Views Manager"))
{
    appendChild<assetsManager>(assetsManagerPtr);
    appendChild<viewsManager>(viewsManagerPtr);
}

core::~core()
{
    terminate();
}

void core::initialize()
{
    terminate();

    if(SDL_Init(SDL_DEFAULT_FLAGS) < 0)
        throw_exception_with_msg(sdl_initialization_error, SDL_GetError());
    if(IMG_Init(SDL_IMAGE_DEFAULT_FLAGS) < 0)
        throw_exception_with_msg(sdl_initialization_error, IMG_GetError());

    window = SDL_CreateWindow(
        getAppName().c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_DEFAULT_WINDOW_FLAGS
    );
    if(!window)
        throw_exception(sdl_window_creation_error, SDL_GetError());
    
    renderer = SDL_CreateRenderer(
        window, -1, SDL_DEFAULT_RENDERER_FLAGS
    );
    if(!renderer)
        throw_exception(sdl_renderer_creation_error, SDL_GetError());

    assetsManagerPtr->loadSprites(assetsRootPath, renderer);

    initialized = true;
}

void core::terminate()
{
    if(renderer)
        SDL_DestroyRenderer(renderer);

    if(window)
        SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    initialized = false;
}

bool core::isInitialized() const
{
    return initialized;
}

bool core::windowShouldClose(const SDL_Event &event) const
{
    switch (event.type)
    {
    case SDL_WINDOWEVENT:
        switch (event.window.event) {

            case SDL_WINDOWEVENT_CLOSE:
                return true;

            default:
                break;
        }
        break;
    case SDL_QUIT:
        return true;
    
    default:
        break;
    }

    return false;
}

void core::execute()
{
    bool shouldRun = true;
    int receivedEvent = 0;

    SDL_Event event = {};
    size_t beforeFrame = 0, afterFrame = 0;

    SDL_RenderClear(renderer);

    while((receivedEvent = SDL_PollEvent(&event)) || shouldRun)
    {
        if(receivedEvent < 1)
            event = {};

        beforeFrame = utilities::getCurrentTimeInMilliseconds();

        if(currentView != viewsManagerPtr->getActiveView())
        {
            currentView = viewsManagerPtr->getActiveView();
            currentView->setChangeActiveViewCallback(
                [this](const std::string &name) {
                    this->getViewsManager()->setActiveView(name);
                }
            );
            
            currentView->setRenderer(renderer);
            currentView->setWindow(window);
            currentView->setAssetsManager(getAssetsManager());

            currentView->setup();

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        if(!currentView)
            throw_exception_without_msg(active_view_missing_error);

        currentView->update(event, beforeFrame - afterFrame);
        SDL_RenderPresent(renderer);
        afterFrame = utilities::getCurrentTimeInMilliseconds();

        if(receivedEvent && windowShouldClose(event))
            return;

        SDL_Delay(16);
    }
}