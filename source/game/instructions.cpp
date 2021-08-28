#include "views/instructions.hpp"

using namespace ksf::views;

register_logger()

void instructions::initialize()
{
    animationsManager = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    viewsManager = getRoot()->getChild<engine::managers::viewsManager>("Views Manager");

    instructionsPtr = animationsManager->getAnimation("Instructions");
}

void instructions::setup()
{
    instructionsPtr->load();
    instructionsPtr->setShouldTransition(true);
    instructionsPtr->setSpritesSize(600,600);

    alpha = 0;
    counter = 0;

    setBackgroundColor(255,255,255,255);
}

void instructions::update(size_t delta)
{
    counter += delta;

    graphics::sprite* currentSprite = instructionsPtr->getCurrentFrame()->getSprite();

    if (counter < fadeDelay && counter % fadeStep == 0)
    {
        alpha = (alpha += fadeStep) <= 255 ? alpha : 255;
        currentSprite->setAlpha(alpha);
    }
    if (counter > showDelay && counter % fadeStep == 0)
    {
        alpha = (alpha -= fadeStep) >= 0 ? alpha : 0;
        currentSprite->setAlpha(alpha);
        if (alpha == 0)
            viewsManager->setActiveView("Game Selection");
    }

    instructionsPtr->play(delta,
        getWindowWidth()/2 - currentSprite->getWidth()/2,
        getWindowHeight()/2 - currentSprite->getHeight()/2
    );
}

void instructions::cleannup()
{
    // Unload sprites
    instructionsPtr->unload();
}