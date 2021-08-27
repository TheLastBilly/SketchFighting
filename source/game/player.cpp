#include "entities/player.hpp"

void ksf::entities::player::setWindowConstraints(int windowWidth, int windowHeight)
{
    setConstraints(0, 
        windowWidth - getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth(),
        windowHeight - getCurrentAnimation()->getCurrentFrame()->getSprite()->getHeight(),
    0);
}

void ksf::entities::player::update(size_t delta)
{
    isMovingHorizontally = false;

    updateTimeCounter += delta;
    if (shouldMove = (updateTimeCounter > 16)) updateTimeCounter = 0;

    // Get directional inputs
    if (currentController.leftPressed())
    {
        horizontalSpeedBuffer -= horizontalSpeed;
        getCurrentAnimation()->flipSprites(graphics::sprite::flip::none);

        isMovingHorizontally = true;
    }
    if (currentController.rightPressed())
    {
        horizontalSpeedBuffer += horizontalSpeed;
        getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);

        isMovingHorizontally = true;
    }
    if (currentController.jumpPressed() && getCoordinates()->getY() == getCoordinates()->getUpperLimit())
    { jump(); }
    
    // Apply gravity
    if (isMidAir =  (getCoordinates()->getY() < getCoordinates()->getUpperLimit()))
    { verticalVelocity -= gravity; }
    verticalSpeedBuffer += verticalVelocity;

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
    if (isMidAir)
    {
        if (verticalVelocity > .0)
            jumpingAnimation->setCurrentFrame(0);
        else if (verticalVelocity < .0)
            jumpingAnimation->setCurrentFrame(1);
        
        setCurrentAnimation(jumpingAnimation);
    }
    else if (isMovingHorizontally)
        setCurrentAnimation(walkingAnimation);
    else
        setCurrentAnimation(idleAnimation);
    getCurrentAnimation()->flipSprites(flip);

    // Play current animation and update hitboxes
    entity::update(delta);
}