#include "views/fadingView.hpp"

using namespace ksf::views;

register_logger()

void fadingView::initialize()
{
    animationsManager = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    viewsManager = getRoot()->getChild<engine::managers::viewsManager>("Views Manager");

    animationPtr = animationsManager->getAnimation(animationName);
}

void fadingView::setup()
{
    animationPtr->load();
    animationPtr->setShouldTransition(true);
    animationPtr->setSpritesSize(width,height);

    alpha = 0;
    counter = 0;

    setBackgroundColor(255,255,255,255);
}

void fadingView::update(size_t delta)
{
    counter += delta;

    graphics::sprite* currentSprite = animationPtr->getCurrentFrame()->getSprite();

    if (counter < fadeDelay && counter % fadeStep == 0)
    {
        alpha = (alpha += fadeStep) <= 255 ? alpha : 255;
        currentSprite->setAlpha(alpha);
    }
    if (counter > duration && counter % fadeStep == 0)
    {
        alpha = (alpha -= fadeStep) >= 0 ? alpha : 0;
        currentSprite->setAlpha(alpha);
        if (alpha == 0)
            viewsManager->setActiveView(nextSceneName);
    }

    animationPtr->play(delta,
        getWindowWidth()/2 - currentSprite->getWidth()/2,
        getWindowHeight()/2 - currentSprite->getHeight()/2
    );
}

void fadingView::cleannup()
{
    // Unload sprites
    animationPtr->unload();
}