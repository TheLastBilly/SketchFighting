#pragma once

#include "engine/graphics/view.hpp"
#include "engine/graphics/animation.hpp"
#include "engine/engine/core.hpp"
#include "engine/engine/entity.hpp"

#include "entities/player.hpp"

namespace ksf
{
    namespace views
    {
        class intro : public graphics::view
        {
        public:
            intro() : view("Intro") {}

            void initialize() override;
            void setup() override;
            void update(size_t delta) override;

        private:
            entities::player *playerPtr = nullptr;
            graphics::animation* idleAnimation = nullptr;
            graphics::animation* walkingAnimation = nullptr;

            engine::managers::animationsManager* animationManagerPtr = nullptr;

            engine::keyboardHandler* keyboardHandlerPtr = nullptr;
        };
    }
}