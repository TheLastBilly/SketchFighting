#include "engine/core.hpp"
#include "utilities/logger.hpp"

#include <thread>

register_logger();

using namespace graphics;
using namespace engine;

core::core(int width, int height):
    node("Root"),

    width(width), 
    height(height), 
    currentView(currentView),

    assetsManagerPtr(std::make_shared<managers::assetsManager>("Assets Manager")),
    viewsManagerPtr(std::make_shared<managers::viewsManager>("Views Manager")),
    animationsManagerPtr(std::make_shared<managers::animationsManager>("Animations Manager")),

    nodesManagerPtr(std::make_shared<managers::nodesManager>("Generic Nodes Manager"))
{
    appendChild<managers::assetsManager>(assetsManagerPtr);
    appendChild<managers::viewsManager>(viewsManagerPtr);
    appendChild<managers::animationsManager>(animationsManagerPtr);
    appendChild<managers::nodesManager>(nodesManagerPtr);
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
    animationsManagerPtr->loadAnimations(getAssetsManager());
    setupViews();

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

void core::setupViews()
{
    for(size_t i = 0; i < getViewsManager()->getChildrenCount(); i++)
    {
        graphics::view* viewPtr = getViewsManager()->getChild<view>(i);

        viewPtr->setRenderer(renderer);
        viewPtr->setWindow(window);
        viewPtr->setAssetsManager(getAssetsManager());
        viewPtr->setAnimationsManager(getAnimationsManager());

        viewPtr->setShouldCloseCallback([this](bool shouldClose){this->shouldClose = true;});
        viewPtr->setChangeActiveViewCallback(
            [this](const std::string &name) {
                this->getViewsManager()->setActiveView(name);
            }
        );

        viewPtr->initialize();
    }
}

void core::execute()
{
    bool shouldRun = true;
    int receivedEvent = 0;

    SDL_Event event = {};
    size_t beforeFrame = 0, afterFrame = 0;
    size_t delta = 0;

    SDL_RenderClear(renderer);

    size_t counter =0;

    while(((receivedEvent = SDL_PollEvent(&event)) || shouldRun) && !this->shouldClose)
    {
        if(receivedEvent < 1)
            event = {};

        SDL_RenderClear(renderer);
        beforeFrame = utilities::getCurrentTimeInMilliseconds();

        if(currentView != viewsManagerPtr->getActiveView())
        {
            currentView = viewsManagerPtr->getActiveView();

            currentView->setup();

            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);

            afterFrame = beforeFrame;
        }

        if(!currentView)
            throw_exception_without_msg(active_view_missing_error);

        delta = beforeFrame - afterFrame;
        currentView->update(event, delta);
        afterFrame = utilities::getCurrentTimeInMilliseconds();
        
#ifdef PRINT_DELTA
        info(std::to_string(counter++) + " delta: " + std::to_string(delta));
#endif

        SDL_RenderPresent(renderer);

        if(receivedEvent && windowShouldClose(event))
            break;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    info("exiting...");
}