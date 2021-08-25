#pragma once

#include "graphics/view.hpp"
#include "graphics/animation.hpp"
#include "engine/core.hpp"
#include "engine/player.hpp"

namespace ksf::views
{
    class intro: public graphics::view
    {
    public:
        intro(): view("Intro") {}

        void setup() override;
        void update(const SDL_Event &event, size_t delta) override;
    
    private:
        graphics::sprite* introSprite = nullptr;
        graphics::animation* introAnimation = nullptr;

        engine::player* playerPtr = nullptr;
    };
}