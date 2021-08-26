#pragma once

#include "engine/graphics/view.hpp"
#include "engine/graphics/animation.hpp"
#include "engine/engine/core.hpp"
#include "engine/engine/entity.hpp"

namespace ksf::views
{
    class intro: public graphics::view
    {
    public:
        intro(): view("Intro") {}

        void initialize() override;
        void setup() override;
        void update(size_t delta) override;
    
    private:
        graphics::sprite* introSprite = nullptr;
        graphics::animation* introAnimation = nullptr;

        engine::keyboardHandler* keyboardHandlerPtr = nullptr;

        engine::entity *playerPtr = nullptr, *enemyPtr = nullptr;
    };
}