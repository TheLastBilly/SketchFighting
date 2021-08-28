#include "views/mainMenu.hpp"

using namespace ksf::views;

register_logger()

void mainMenu::initialize()
{
    animationsManager = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    viewsManager = getRoot()->getChild<engine::managers::viewsManager>("Views Manager");
    nodesManager = getRoot()->getChild<engine::managers::nodesManager>("Keyboard Handler");
    keyboardHandler = getRoot()->getChild<engine::keyboardHandler>("Keyboard Handler");

    nodesManager->registerNode(
        title = new engine::entity("Title Button")
    );
    nodesManager->registerNode(
        quit = new engine::entity("Quit Button")
    );
    nodesManager->registerNode(
        play = new engine::entity("Start Button")
    );
    nodesManager->registerNode(
        arrow = new engine::entity("Arrow")
    );

    arrowOn = animationsManager->getAnimation("Main Menu Select On");
    arrowOff = animationsManager->getAnimation("Main Menu Select Off");

    title->setCurrentAnimation(animationsManager->getAnimation("Main Menu Title"));
    quit->setCurrentAnimation(animationsManager->getAnimation("Main Menu Quit"));
    play->setCurrentAnimation(animationsManager->getAnimation("Main Menu Play"));
    arrow->setCurrentAnimation(arrowOff);
}

void mainMenu::setup()
{
    // Load animations
    title->getCurrentAnimation()->load();
    quit->getCurrentAnimation()->load();
    play->getCurrentAnimation()->load();

    arrowOn->load();
    arrowOff->load();

    title->getCurrentAnimation()->setSpritesSize(500, 500);
    /*quit->getCurrentAnimation()->setSpritesSize(300, 300);
    play->getCurrentAnimation()->setSpritesSize(300, 300);
    arrow->getCurrentAnimation()->setSpritesSize(300, 300);*/

    // Setup animations
    arrow->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);
    quit->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);
    play->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);
    arrow->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);

    // Place all the elements accordingly
    title->centerToScreen(getWindowWidth(), getWindowHeight());
    title->getCoordinates()->moveVertically(100);

    play->centerToScreen(getWindowWidth(), getWindowHeight());
    play->getCoordinates()->moveVertically(100);
    quit->setCoordinates(play->getCoordinates());
    quit->getCoordinates()->moveVertically(150);

    arrow->setCoordinates(play->getCoordinates());

    option = 1;

    // Cleare render and set background color
    SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
    SDL_RenderClear(getRenderer());
}

void mainMenu::update(size_t delta)
{
    static size_t counter = 0;

    if (!optionSelected)
    {
        if (keyboardHandler->isKeyActive(engine::keyboardHandler::key::up))
            option = 1;
        else if (keyboardHandler->isKeyActive(engine::keyboardHandler::key::down))
            option = 2;

        if (keyboardHandler->isKeyActive(engine::keyboardHandler::key::enter))
        {
            optionSelected = true;
            arrow->setCurrentAnimation(arrowOn);
        }
    }

    switch (option)
    {
    case 1:
        arrow->setCoordinates(play->getCoordinates());
        break;
    case 2:
        arrow->setCoordinates(quit->getCoordinates());
        break;
    default:
        break;
    }

    arrow->getCoordinates()->moveHorizontally(-150);

    // Update animations
    title->update(delta);
    quit->update(delta);
    play->update(delta);
    arrow->update(delta);

    if (optionSelected)
    {
        if (counter < selectDelay)
        {
            counter += delta;
            return;
        }
        switch (option)
        {
        case 1:
            shouldClose(true);
            break;
        case 2:
            shouldClose(true);
            break;
        default:
            break;
        }
    }
}

void mainMenu::cleannup()
{
    // Unload sprites
    title->getCurrentAnimation()->unload();
    quit->getCurrentAnimation()->unload();
    play->getCurrentAnimation()->unload();
    arrow->getCurrentAnimation()->unload();

    arrowOn->unload();
    arrowOff->unload();
}