#pragma once

#include "engine/managers/animationsManager.hpp"
#include "views/map.hpp"

namespace ksf
{
    namespace maps
    {
        class genericBackground: public engine::node
        {
        public:
            genericBackground(const std::string &name, engine::managers::animationsManager* animationsManager): node(name), animationsManager(animationsManager) {}

            virtual graphics::animation* getBackground() = 0;
            virtual graphics::animation* getIntroAnimation() = 0;
            virtual graphics::animation* getNameAnimation() = 0;

            virtual int getFloorHeight() = 0;

        protected:
            engine::managers::animationsManager* animationsManager;
        };
    }
}