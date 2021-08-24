#ifndef view_hpp__
#define view_hpp__

#include <memory>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include "engine/node.hpp"
#include "utilities/utilities.hpp"

namespace graphics
{
    class view: public engine::node
    {
    public:
        virtual void setup() = 0;
        virtual void update(const SDL_Event &event, size_t delta) = 0;

    public:
        view(const std::string &name): node(name) {}

        inline void set_change_active_view_callback(const std::function<void(const std::shared_ptr<view>&)> &callback)
        {
            change_active_view_callback = callback;
        }
        inline void set_get_renderer_callback(const std::function<SDL_Renderer*()> &callback)
        {
            get_renderer_callback = callback;
        }
        inline void set_get_window_callback(const std::function<SDL_Window*()> &callback)
        {
            get_window_callback = callback;
        }

        SDL_Renderer* get_renderer() const
        {
            if(!get_renderer_callback)
                throw_exception_with_msg(utilities::null_callback_error, "get_renderer callback was not set");
            
            return get_renderer_callback();
        }

        SDL_Window* get_window() const
        {
            if(!get_window_callback)
                throw_exception_with_msg(utilities::null_callback_error, "get_window callback was not set");
            
            return get_window_callback();
        }

        void change_active_node(const std::shared_ptr<node> &child) const
        {
            if(!change_active_view_callback)
                throw_exception_with_msg(utilities::null_callback_error, "change_active_node callback was not set");
            
            change_active_view_callback(child->cast<view>());
        }
    private:
        std::function<void(const std::shared_ptr<view>&)> change_active_view_callback;
        
        std::function<SDL_Renderer*()> get_renderer_callback;
        std::function<SDL_Window*()> get_window_callback;
    };
}

#endif