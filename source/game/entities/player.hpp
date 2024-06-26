#pragma once

#include <functional>

#include "engine/entity.hpp"
#include "engine/inputs.hpp"

namespace ksf
{
    namespace entities
    {
        class player: public engine::entity
        {
        public:
            enum direction
            {
                left, right, none
            };

            class controller
            {
            public:
                inline void setLeftCallback(const std::function<bool()> &callback)
                { this->leftCallback = callback; }
                inline bool leftPressed() const
                {
                    if (leftCallback)
                        return leftCallback();

                    return false;
                }
                inline void setRightCallback(const std::function<bool()> &callback)
                { this->rightCallback = callback; }
                inline bool rightPressed() const
                {
                    if (rightCallback)
                        return rightCallback();

                    return false;
                }
                inline void setUpCallback(const std::function<bool()> &callback)
                { this->upCallback = callback; }
                inline bool upPressed() const
                {
                    if (upCallback)
                        return upCallback();

                    return false;
                }
                inline void setDownCallback(const std::function<bool()> &callback)
                { this->downCallback = callback; }
                inline bool downPressed() const
                {
                    if (downCallback)
                        return downCallback();

                    return false;
                }
                
                inline void setLightCallback(const std::function<bool()> &callback)
                { this->lightCallback = callback; }
                inline bool lightPressed() const
                {
                    if (lightCallback)
                        return lightCallback();

                    return false;
                }
                inline void setHeavyCallback(const std::function<bool()> &callback)
                { this->heavyCallback = callback; }
                inline bool heavyPressed() const
                {
                    if (heavyCallback)
                        return heavyCallback();

                    return false;
                }
                inline void setJumpCallback(const std::function<bool()> &callback)
                { this->jumpCallback = callback; }
                inline bool jumpPressed() const
                {
                    if (jumpCallback)
                        return jumpCallback();

                    return false;
                }

            private:
                std::function<bool()> 
                    leftCallback,
                    rightCallback, 
                    upCallback, 
                    downCallback,
                    
                    lightCallback, 
                    heavyCallback,
                    jumpCallback;
            };
        public:
            player(
                const std::string &name,
                graphics::animation *idleAnimation,
                graphics::animation* walkingAnimation,
                graphics::animation* jumpingAnimation,
                graphics::animation* hitAnimation,
                graphics::animation* blockAnimation,
                graphics::animation* attackAnimation
            ): 
                entity(name),

                idleAnimation(idleAnimation),
                walkingAnimation(walkingAnimation),
                jumpingAnimation(jumpingAnimation),
                hitAnimation(hitAnimation),
                blockAnimation(blockAnimation),
                attackAnimation(attackAnimation)
            {
                setCurrentAnimation(idleAnimation);
                jumpingAnimation->setRepeat(false);

                width = idleAnimation->getCurrentFrame()->getSprite()->getWidth();
                height = idleAnimation->getCurrentFrame()->getSprite()->getHeight();
            }
        
            void update(size_t delta);
            void setWindowConstraints(int windowWidth, int windowHeight);
            void setFloorHeight(int height);
            void setWindowBorders(int x, int width);
            
            inline void setGravity(float gravity)
            { this->gravity = gravity; }
            float getGravity() const
            { return this->gravity; }
            
            inline void setHorizontalSpeed(float horizontalSpeed)
            { this->horizontalSpeed = horizontalSpeed; }
            float getHorizontalSpeed() const
            { return this->horizontalSpeed; }
            
            inline void setJumpSpeed(float jumpSpeed)
            { this->jumpSpeed = jumpSpeed; }
            float getJumpSpeed() const
            { return this->jumpSpeed; }

            void setController(const controller& c)
            { this->currentController = c; }
            controller* getController()
            { return &currentController; }

            inline void jump()
            { verticalVelocity = jumpSpeed; }
            inline void fallFaster()
            { verticalVelocity = -jumpSpeed * 1.15; }

            inline bool isMidAir()
            { return getCoordinates()->getY() < getCoordinates()->getUpperLimit(); }

            void load()
            {
                idleAnimation->load();
                walkingAnimation->load();
                jumpingAnimation->load();
                hitAnimation->load();
                blockAnimation->load();
                attackAnimation->load();

                setSpritesSize(this->width, this->height);
            }
            void unload()
            {
                idleAnimation->unload();
                walkingAnimation->unload();
                jumpingAnimation->unload();
                hitAnimation->unload();
                blockAnimation->unload();
                attackAnimation->unload();
            }

            void setSpritesSize(int width, int height)
            {
                this->height = height;
                this->width = width;

                idleAnimation->setSpritesSize(width, height);
                walkingAnimation->setSpritesSize(width, height);
                jumpingAnimation->setSpritesSize(width, height);
                hitAnimation->setSpritesSize(width, height);
                blockAnimation->setSpritesSize(width, height);
                attackAnimation->setSpritesSize(width, height);
            }

            inline void setOponent(player* oponent)
            { this->oponent = oponent; }
            inline void setTouchingOponent(bool touchingOponent)
            { this->touchingOponent = touchingOponent; }

            inline int getHealth() const
            {
                return health;
            }
            inline void reduceHealth(int damage)
            {
                if (!canReceiveDamage)
                    return;
                
                damageReceived = damage;
            }

            inline direction getDirection() const
            {
                return currentDirection;
            }
            inline void setDirection(direction newDirection)
            {
                currentDirection = newDirection;
            }

            virtual void flipToTheRight()
            {
                getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);
            }
            virtual void flipToTheLeft()
            {
                getCurrentAnimation()->flipSprites(graphics::sprite::flip::none);
            }

            inline void setPaused(bool paused)
            {
                this->paused = paused;
            }

        private:
            graphics::animation
                * idleAnimation = nullptr,
                * walkingAnimation = nullptr,
                * jumpingAnimation = nullptr,
                * hitAnimation = nullptr,
                * blockAnimation = nullptr,
                * attackAnimation = nullptr;
            
            player* oponent = nullptr;
            
            size_t updateTimeCounter = 0, damageTimeCounter = 0;

            int
                height = 0,
                width = 0,
                health = 100,
                damageReceived = 0,
                attackDamage = 20,
                horizontalSpeedMultiplier = 0;

            float
                verticalVelocity = .0,
                horizontalSpeedBuffer = .0,
                verticalSpeedBuffer = .0;

            float
                gravity = .0,
                horizontalSpeed = .0,
                jumpSpeed = .0;
            
            bool
                shouldMove = false,
                isMovingHorizontally = false,
                canReceiveDamage = true,
                canMove = true,
                hitAttempted = false,
                isAttacking = false,
                hasBeenHit = false,
                isBlocking = false,
                touchingOponent = false,
                paused = false;

            controller currentController = {};

            direction currentDirection = direction::left;

            const size_t damageCooldown = 500;
        };
    }
}