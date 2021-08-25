#pragma once

#include <memory>

#include "engine/node.hpp"
#include "graphics/animation.hpp"
#include "engine/managers/nodesManager.hpp"
#include "math/coordinates.hpp"

namespace engine
{
    class player: public node
    {
    public:
        register_exception(animation_not_defined_error, "animation has not been defined");

    public:
        player(const std::string &name): 
            node(name),
            coordinatesPtr(new math::coordinates("coordinates"))
        { appendChild(coordinatesPtr); }

        inline math::coordinates* getCoordinates() const
        { return coordinatesPtr.get(); }

        inline void setCurrentAnimation(graphics::animation* animation)
        { currentAnimation = animation; }
        inline graphics::animation* getCurrentAnimation() const 
        { return currentAnimation; }

        void playAnimation(int delta) const
        {
            if(!currentAnimation)
                throw_exception_without_msg(animation_not_defined_error);
            
            currentAnimation->play(delta, coordinatesPtr->getX(), coordinatesPtr->getY());
        }

    private:
        graphics::animation* currentAnimation = nullptr;

    private:
        std::shared_ptr<math::coordinates> coordinatesPtr;
    };
}