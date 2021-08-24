#include "graphics/core.hpp"
#include "utilities/logger.hpp"

register_logger();

using namespace graphics;

core::~core()
{
    terminate();
}

void core::initialize()
{
    terminate();

    if(SDL_Init(SDL_DEFAULT_FLAGS) < 0)
        throw_exception_with_msg(sdl_initialization_error, SDL_GetError());

    window = SDL_CreateWindow(
        SDL_WINDOW_NAME,
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

    initialized = true;
}

void core::terminate()
{
    if(renderer)
        SDL_DestroyRenderer(renderer);

    if(window)
        SDL_DestroyWindow(window);

    initialized = false;
}

bool core::is_initialized() const
{
    return initialized;
}

bool core::window_should_close(const SDL_Event &event) const
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
    bool should_run = true;
    int recevied_event = 0;

    SDL_Event event = {};
    size_t before_frame = 0, after_frame = 0;

    SDL_RenderClear(renderer);

    while((recevied_event = SDL_PollEvent(&event)) || should_run)
    {
        if(recevied_event < 1)
            event = {};

        before_frame = utilities::get_current_time_in_milliseconds();

        if(next_view)
        {
            next_view->set_change_active_view_callback(
                [this](const std::shared_ptr<view> &next_view) {
                    this->next_view = next_view;
                }
            );
            next_view->set_get_renderer_callback(
                [this]() {
                    return renderer;
                }
            );
            next_view->set_get_window_callback(
                [this]() {
                    return window;
                }
            );
            next_view->setup();
            current_view = next_view;
            next_view = nullptr;

            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        current_view->update(event, before_frame - after_frame);
        SDL_RenderPresent(renderer);
        after_frame = utilities::get_current_time_in_milliseconds();

        if(recevied_event && window_should_close(event))
            return;

        SDL_Delay(16);
    }
}