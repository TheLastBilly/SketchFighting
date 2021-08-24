#ifndef view_hpp__
#define view_hpp__

#include <memory>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include "utilities/utilities.hpp"

namespace graphics
{
    class view 
    {
    public:
        virtual void setup() = 0;
        virtual void update(const SDL_Event &event, size_t delta) = 0;

    public:
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
    
    protected:
        inline void append_child(std::shared_ptr<view> &child)
        {
            child->set_parent(std::shared_ptr<view>(this));
            children.push_back(child);
        }
        inline void remove_child(size_t index)
        {
            get_child(index);
            children.erase(children.begin() + index);
        }
        inline void set_parent(const std::shared_ptr<view> &parent)
        {
            this->parent = parent;
        }
        inline size_t get_children_count() const
        {
            return children.size();
        }
        
        const std::shared_ptr<view> get_child(size_t index) const
        {
            if(children.size() <= index)
                throw_out_of_bounds_error(children, index);

            return children.at(index);
        }

        void change_active_view(const std::shared_ptr<view> &child) const
        {
            if(!change_active_view_callback)
                throw_exception_with_msg(utilities::null_callback_error, "change_active_view callback was not set");
            
            change_active_view_callback(child);
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

    private:
        std::vector<std::shared_ptr<view>> children;
        std::shared_ptr<view> parent;

        std::function<void(const std::shared_ptr<view>&)> change_active_view_callback;
        
        std::function<SDL_Renderer*()> get_renderer_callback;
        std::function<SDL_Window*()> get_window_callback;
    };
}

#endif