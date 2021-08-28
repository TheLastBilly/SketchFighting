#pragma once

#include "engine/managers/animationsManager.hpp"
#include "entities/player.hpp"

namespace ksf
{
    namespace players
    {
        class genericPlayer: public engine::node
        {
        public:
            genericPlayer(const std::string &name, engine::managers::animationsManager* animationsManager): node(name), animationsManager(animationsManager) {}

            virtual entities::player* createPlayer() = 0;
            virtual graphics::animation* getIntroAnimation() = 0;
            virtual graphics::animation* getNameAnimation() = 0;

        protected:
            engine::managers::animationsManager* animationsManager;
        };
    }
}