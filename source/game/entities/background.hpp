#pragma once

#include <functional>

#include "engine/entity.hpp"
#include "engine/inputs.hpp"

namespace ksf
{
    namespace entities
    {
        class background : public engine::entity
        {
        public:
            background(const std::string& name, graphics::animation* animation) : entity(name) 
            { setCurrentAnimation(animation); }

            void centerToScreen(int screenWidth, int screenHeight)
            {
                math::coordinates* coordinates = getCoordinates();
                const size_t sprites = getCurrentAnimation()->getFrameCount();

                for (size_t i = 0; i < sprites; i++)
                {
                    graphics::sprite* currentSprite = getCurrentAnimation()->getFrame(i)->getSprite();
                    coordinates->setX(screenWidth / 2 - currentSprite->getWidth() / 2);
                    coordinates->setX(screenHeight / 2 - currentSprite->getHeight() / 2);
                }
            }
        };
    }
}