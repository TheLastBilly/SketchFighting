#ifndef menu_hpp__
#define menu_hpp__

#include "graphics/view.hpp"
#include "engine/assetsManager.hpp"

namespace ui
{
    class menu: public graphics::view
    {
    public:
        menu(const std::string &name): view(name) {}

        void setup() override
        {
            mainSprite = getRoot()->getChild<engine::assetsManager>("Assets Manager")->getChild<graphics::sprite>("Test");
        }
        void update(const SDL_Event &event, size_t delta) override
        {
            mainSprite->render(0,0);
        }
    
    private:
        graphics::sprite* mainSprite;
    };
}

#endif