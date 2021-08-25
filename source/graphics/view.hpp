#ifndef view_hpp__
#define view_hpp__

#include <memory>
#include <vector>
#include <functional>

#include <SDL2/SDL.h>

#include <engine/assetsManager.hpp>

#include "engine/node.hpp"
#include "utilities/generics.hpp"

namespace graphics
{
    class view: public engine::node
    {
    public:
        struct resolution
        { int width, height; };

    public:
        view(const std::string &name): node(name) {}

    public:
        virtual void setup() = 0;
        virtual void update(const SDL_Event &event, size_t delta) = 0;

    public:        
        inline void setRenderer(SDL_Renderer *renderer)
        { this->renderer = renderer; }
        void setWindow(SDL_Window *window)
        {
            this->window = window;
            SDL_GetWindowSize(window, &width, &height);
        }

        inline SDL_Renderer* getRenderer() const
        { return renderer; }
        inline SDL_Window* getWindow() const
        { return window; }

        inline int getWindowHeight() const
        { return height; } 
        inline int getWindowWidth() const
        { return width; } 

        inline void setAssetsManager(engine::assetsManager* manager)
        { assetsManagerPtr = manager; }
        inline engine::assetsManager* getAssetsManager() const
        { return assetsManagerPtr; }

        inline void setChangeActiveViewCallback(const std::function<void(const std::string &name)> &callback)
        { changeActiveViewCallback = callback; }
        void changeActiveNode(const std::string &name) const
        {
            if(!changeActiveViewCallback)
                throw_exception_with_msg(utilities::null_callback_error, "changeActiveNode callback was not set");
            
            changeActiveViewCallback(name);
        }
    private:
        std::function<void(const std::string &name)> changeActiveViewCallback;
        
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        engine::assetsManager* assetsManagerPtr = nullptr;

        int height = 0, width = 0;
    };
}

#endif