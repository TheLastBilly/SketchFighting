#pragma once

#include "engine/managers/assetsManager.hpp"
#include "engine/managers/animationsManager.hpp"

#include "entities/player.hpp"

namespace ksf
{
    namespace utilities
    {
        class contentLoader
        {
        public:
            static void loadSprites(engine::managers::assetsManager* manager);
            static void loadAnimations(engine::managers::animationsManager* animationsManagerPtr, engine::managers::assetsManager* assetsManaterPtr);
        };
    }
}