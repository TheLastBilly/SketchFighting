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

        const math::collisions::hitbox* getHitbox() const
        { return &hitbox; }

        void updateHitbox()
        {
            hitbox.upperVector.a.setX(coordinates.getX());
            hitbox.upperVector.a.setY(coordinates.getY());

            hitbox.upperVector.b.setX(coordinates.getX() + currentAnimation->getCurrentFrame()->getSprite()->getWidth());
            hitbox.upperVector.b.setY(hitbox.upperVector.a.getY());

            hitbox.lowerVector = hitbox.upperVector;
            hitbox.lowerVector.a.setY(coordinates.getY() + currentAnimation->getCurrentFrame()->getSprite()->getHeight());
            hitbox.lowerVector.b.setY(hitbox.lowerVector.a.getY());
        }

        void setConstraints(int minX, int maxX, int minY, int maxY)
        {
            coordinates.setHorizontalRange(minX, maxX);
            coordinates.setVerticalRange(minY, maxY);

            coordinates.moveHorizontally(0);
            coordinates.moveVertically(0);
        }

        void update(int delta)
        {
            if(!currentAnimation)
                throw_exception_without_msg(animation_not_defined_error);
            
            currentAnimation->play(delta, coordinates.getX(), coordinates.getY());
            updateHitbox();
        }

    private:
        graphics::animation* currentAnimation = nullptr;

    private:
        math::coordinates coordinates;
        math::collisions::hitbox hitbox;
    };
}