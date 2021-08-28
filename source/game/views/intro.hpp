#pragma once

#include "engine/graphics/view.hpp"
#include "engine/graphics/animation.hpp"
#include "engine/engine/core.hpp"
#include "engine/engine/entity.hpp"

#include "entities/player.hpp"
#include "views/map.hpp"

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
            void cleannup() override;

        private:
            entities::player *playerPtr = nullptr;
            entities::player* player2Ptr = nullptr;

            entities::background* backgroundPtr = nullptr;
            entities::floor* floorPtr = nullptr;

            graphics::animation* idleAnimation = nullptr;
            graphics::animation* walkingAnimation = nullptr;
            graphics::animation* jumpingAnimation = nullptr;
            graphics::animation* backgroundAnimation = nullptr;

            engine::managers::animationsManager* animationManagerPtr = nullptr;
            engine::managers::collisionsManager* collisionManagerPtr = nullptr;

            engine::keyboardHandler* keyboardHandlerPtr = nullptr;
        };
    }
}