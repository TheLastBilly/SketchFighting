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

            virtual entities::player* createPlayer(const std::string& name) = 0;
            virtual graphics::animation* getIntroAnimation() = 0;
            virtual graphics::animation* getNameAnimation() = 0;

            inline void setSelected(bool selected)
            { this->selected = selected; }
            inline bool getSelected() const
            { return selected; }

        protected:
            engine::managers::animationsManager* animationsManager;
            bool selected = false;
        };
    }
}