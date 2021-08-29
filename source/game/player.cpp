#include "entities/player.hpp"
#include "utilities/logger.hpp"

register_logger()

void ksf::entities::player::setWindowConstraints(int windowWidth, int windowHeight)
{
    setConstraints(0, 
        windowWidth - getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth(),
        windowHeight - getCurrentAnimation()->getCurrentFrame()->getSprite()->getHeight(),
    0);
}

void ksf::entities::player::setFloorHeight(int height)
{
    setVerticalContraints(height - getCurrentAnimation()->getCurrentFrame()->getSprite()->getHeight(), 0);
}

void ksf::entities::player::setWindowBorders(int x, int width)
{
    setHorizontalContraints(x, width - getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth());
}

void ksf::entities::player::update(size_t delta)
{
    isMovingHorizontally = false;
    horizontalSpeedMultiplier = 0;

    updateTimeCounter += delta;
    if (shouldMove = (updateTimeCounter > 16)) updateTimeCounter = 0;

    if (getCurrentAnimation()->isDonePlaying())
    {
        canMove = true;
        if (isAttacking)
            isAttacking = false;
        if (hasBeenHit)
            hasBeenHit = false;
        if (isBlocking = false)
            isBlocking = true;
        
        getCurrentAnimation()->reset();
    }

    if (isAttacking && touchingPlayer != nullptr)
        touchingPlayer->reduceHealth(attackDamage);
    
    if (!canReceiveDamage)
    {
        if (damageTimeCounter < damageCooldown)
            damageTimeCounter += delta;
        else
        {
            damageTimeCounter = 0;
            canReceiveDamage = true;
        }
    }

    if (canReceiveDamage && damageReceived != 0 && this->touchingPlayer != nullptr)
    {
        direction origin = direction::none;
        if (
            // This is due in a couple ours, f*ck it, I don't care anymore
            (((origin = direction::right) != direction::none && touchingPlayer->getDirection() != direction::left) && getCoordinates()->getX() > touchingPlayer->getCoordinates()->getX()) ||
            (((origin = direction::left) != direction::none && touchingPlayer->getDirection() != direction::right) && getCoordinates()->getX() < touchingPlayer->getCoordinates()->getX())
         )
        {
            if (getDirection() != direction::none && origin == getDirection())
            {
                switch (getDirection())
                {
                case direction::left:
                    flipToTheRight();
                    break;
                case direction::right:
                    flipToTheLeft();
                    break;
                default:
                    break;
                }

                isBlocking = true;
                canReceiveDamage = canMove = false;
                info("Blocked!");
            }
            else
            {
                info("Received damage!");
                canReceiveDamage = canMove = false;
                hitAnimation->reset();
                hitAnimation->flipSprites(getCurrentAnimation()->getSpritesFlip());
                hasBeenHit = true;

                health = health - damageReceived;
                if (health < 0) health = 0;
            }
        }
        damageReceived = 0;
    }

    // Get inputs
    setDirection(none);
    if (canMove || isMidAir())
    {
        if (currentController.leftPressed())
        {
            horizontalSpeedMultiplier = -1;
            flipToTheLeft();

            isMovingHorizontally = true;
        }
        if (currentController.rightPressed())
        {
            horizontalSpeedMultiplier = 1;
            flipToTheRight();

            isMovingHorizontally = true;
        }
        if (currentController.jumpPressed() && !isMidAir())
        {
            jump();
        }
        if (currentController.lightPressed() && (!isAttacking || !hasBeenHit))
        {
            canMove = false;
            isAttacking = true;
            attackAnimation->reset();
            attackAnimation->setRepeat(false);
            attackAnimation->flipSprites(getCurrentAnimation()->getSpritesFlip());
        }
    }
    
    // Apply velocities
    verticalVelocity -= gravity;
    verticalSpeedBuffer += verticalVelocity;
    horizontalSpeedBuffer += horizontalSpeed * horizontalSpeedMultiplier;

    // Apply movements
    if (shouldMove)
    {
        getCoordinates()->moveVertically(-verticalVelocity *delta);
        verticalSpeedBuffer = .0;

        getCoordinates()->moveHorizontally(horizontalSpeedBuffer * delta);
        horizontalSpeedBuffer = .0;
    }


    // Set animations
    graphics::sprite::flip flip = getCurrentAnimation()->getSpritesFlip();
    if (isAttacking)
        setCurrentAnimation(attackAnimation);
    else if (hasBeenHit)
        setCurrentAnimation(hitAnimation);
    else if (isBlocking)
        setCurrentAnimation(blockAnimation);
    else
    {
        if (isMidAir())
        {
            if (verticalVelocity > .0)
                jumpingAnimation->setCurrentFrame(0);
            else if (verticalVelocity < .0)
                jumpingAnimation->setCurrentFrame(1);

            setCurrentAnimation(jumpingAnimation);
        }
        else
        {
            if (isMovingHorizontally)
                setCurrentAnimation(walkingAnimation);
            else
                setCurrentAnimation(idleAnimation);
        }
    }
    getCurrentAnimation()->flipSprites(flip);

    // Play current animation and update hitboxes
    entity::update(delta);
}