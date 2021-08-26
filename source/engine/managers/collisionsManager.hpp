#pragma once

#include <utility>
#include <vector>
#include <functional>

#include "utilities/generics.hpp"

#include "engine/entity.hpp"
#include "engine/managers/genericManager.hpp"
#include "math/collisions.hpp"

namespace engine::managers
{
    class collisionEvent: public node
    {
    public:
        collisionEvent(const std::string &name, entity *entityA, entity *entityB, const std::function<void(entity*, entity*)> &callback):
            node(name), entityA(entityA), entityB(entityB), callback(callback) {}

        inline bool collisionHappened() const
        { return active && math::collisions::hitboxesCollide(*entityA->getHitbox(), *entityB->getHitbox()); }
        inline void runCallback()
        { callback(entityA, entityB); }

        inline bool getActive() const
        { return active; }
        inline void setActive(bool active)
        { this->active = active; }

    private:
        bool active = false;

        entity *entityA, *entityB;
        std::function<void(entity*, entity*)> callback;
    };

    class collisionsManager: public genericManager<collisionEvent>
    {
    public:
        collisionsManager(const std::string &name): genericManager(name) {}

        inline void regsiterCollisionEvent(collisionEvent* request)
        { registerElement(request); }

        inline collisionEvent* getCollision(const std::string &name)
        { return getObject(name); }

        void setAllCollisionsEnable( bool enable )
        {
            for(const auto &event: elements)
                event->setActive(enable);
        }

        void runCollisions()
        {
            for(const auto &event: elements)
            {
                if(event->collisionHappened())
                    event->runCallback();
            }
        }
    };
}