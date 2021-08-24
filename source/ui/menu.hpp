#ifndef menu_hpp__
#define menu_hpp__

#include "graphics/view.hpp"

namespace ui
{
    class menu: public graphics::view
    {
        void setup() override
        {
            SDL_Renderer *renderer = this->get_renderer();
        }
        void update(const SDL_Event &event, size_t delta) override
        {
            
        }
    };
}

#endif