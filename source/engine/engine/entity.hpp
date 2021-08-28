#pragma once

#include <memory>

#include "engine/node.hpp"
#include "graphics/animation.hpp"
#include "engine/managers/nodesManager.hpp"
#include "math/coordinates.hpp"
#include "math/collisions.hpp"

namespace engine
{
    class entity: public node
    {
    public:
        register_exception(animation_not_defined_error, "animation has not been defined");

    public:
        entity(const std::string &name):  node(name) {}

        inline math::coordinates* getCoordinates()
        { return &coordinates; }

        inline void setCurrentAnimation(graphics::animation* animation)
        { currentAnimation = animation; }
        inline graphics::animation* getCurrentAnimation() const 
        { return currentAnimation; }

        inline const math::collisions::hitbox* getHitbox() const
        { return &hitbox; }

        void updateHitbox(int width, int height)
        {
            hitbox.upperVector.a.setX(coordinates.getX());
            hitbox.upperVector.a.setY(coordinates.getY());

            hitbox.upperVector.b.setX(coordinates.getX() + width);
            hitbox.upperVector.b.setY(hitbox.upperVector.a.getY());

            hitbox.lowerVector = hitbox.upperVector;
            hitbox.lowerVector.a.setY(coordinates.getY() + height);
            hitbox.lowerVector.b.setY(hitbox.lowerVector.a.getY());
        }

        void setConstraints(int minX, int maxX, int minY, int maxY)
        {
            setHorizontalContraints(minX, maxX);
            setVerticalContraints(minY, maxY);
        }

        void setHorizontalContraints(int minX, int maxX)
        {
            coordinates.setHorizontalRange(minX, maxX);
        }
        void setVerticalContraints(int minY, int maxY)
        {
            coordinates.setVerticalRange(minY, maxY);
        }

        void update(int delta)
        {
            if (currentAnimation)
            {
                currentAnimation->play(delta, coordinates.getX(), coordinates.getY());
                updateHitbox(currentAnimation->getCurrentFrame()->getSprite()->getWidth(), currentAnimation->getCurrentFrame()->getSprite()->getHeight());
            }
        }

        void centerToScreen(int screenWidth, int screenHeight)
        {
            if (!currentAnimation)
                throw_exception_without_msg(animation_not_defined_error);
            
            math::coordinates* coordinates = getCoordinates();
            const size_t sprites = getCurrentAnimation()->getFrameCount();

            for (size_t i = 0; i < sprites; i++)
            {
                graphics::sprite* currentSprite = getCurrentAnimation()->getFrame(i)->getSprite();
                coordinates->setX(screenWidth / 2 - currentSprite->getWidth() / 2);
                coordinates->setX(screenHeight / 2 - currentSprite->getHeight() / 2);
            }
        }

    protected:
        graphics::animation* currentAnimation = nullptr;

    protected:
        math::coordinates coordinates;
        math::collisions::hitbox hitbox;
    };
}