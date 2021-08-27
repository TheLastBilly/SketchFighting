#pragma once

#include "engine/managers/assetsManager.hpp"
#include "engine/managers/animationsManager.hpp"

namespace ksf
{
    namespace utilities
    {
        class loader
        {
        public:
            static void loadSprites(engine::managers::assetsManager* manager);
            static void loadAnimations(engine::managers::animationsManager* animationsManagerPtr, engine::managers::assetsManager* assetsManaterPtr);
        };
    }
}