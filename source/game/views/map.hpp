#pragma once

#include "graphics/view.hpp"

#include "engine/entity.hpp"
#include "engine/inputs.hpp"

#include "engine/managers/collisionsManager.hpp"

#include "entities/player.hpp"
#include "entities/globalSettings.hpp"

namespace ksf
{
    namespace views
    {
        class map : public graphics::view
        {
        public:
            class background : public engine::entity
            {
            public:
                background(const std::string& name, graphics::animation* animation) : entity(name)
                {
                    setCurrentAnimation(animation);
                }

                inline void load()
                { getCurrentAnimation()->load(); }
                inline void unload()
                { getCurrentAnimation()->unload(); }
            };

            class floor : public engine::entity
            {
            public:
                floor(const std::string& name, int width, int height, int x, int y) : entity(name)
                {
                    coordinates.setX(x);
                    coordinates.setY(y);

                    updateHitbox(width, height);
                }
            };

        public:
            map() : view("Map") {}

            void setup() override;
            void update(size_t delta) override;
            void cleannup() override;

            void fixScaling();

        protected:
            void initialize() override;

        protected:
            int floorHeight = 0;

            bool initialScaling = true;

            entities::player
                * player1Ptr = nullptr,
                * player2Ptr = nullptr;

            engine::entity
                * pencilOk = nullptr,
                * pencilBad = nullptr,
                * p1 = nullptr,
                * p2 = nullptr,
                * circle = nullptr;

            int windowWidth = 0, windowHeight = 0;

            const int healthBarLenght = 5;

            background* backgroundPtr = nullptr;

            engine::managers::collisionsManager* collisionsManager = nullptr;
            engine::managers::nodesManager* nodesManager = nullptr;
            engine::managers::animationsManager* animationsManager = nullptr;

            engine::keyboardHandler* keyboardHandlerPtr = nullptr;

            entities::globalSettings* globalSettings = nullptr;
        };
    }
}