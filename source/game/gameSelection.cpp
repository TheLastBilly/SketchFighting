#include "views/gameSelection.hpp"

using namespace ksf::views;
using namespace engine;

register_logger()

void gameSelection::initialize()
{
    animationsManager = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    viewsManager = getRoot()->getChild<engine::managers::viewsManager>("Views Manager");
    nodesManager = getRoot()->getChild<engine::managers::nodesManager>("Generic Nodes Manager");
    keyboardHandler = getRoot()->getChild<engine::keyboardHandler>("Keyboard Handler");
    globalSettings = nodesManager->getChild<entities::globalSettings>("Global Settings");

    // Get players (loaders)
    players::genericPlayer* player = nullptr;
    nodesManager->registerNode(player = new players::hammerGuy(animationsManager));
    players.push_back(player);
    nodesManager->registerNode(player = new players::miso(animationsManager));
    players.push_back(player);

    // Register backgrounds
    maps::genericBackground* background = nullptr;
    nodesManager->registerNode(background = new maps::beach(animationsManager));
    maps.push_back(background);

    // Frame
    nodesManager->registerNode(selectionFrame = new entity("Selection Frame"));
    selectionFrame->setCurrentAnimation(animationsManager->getAnimation("Selection Frame"));
    
    // Selection Arrow
    nodesManager->registerNode(selectionArrow = new entity("Selection Arrow"));

    // Player name
    nodesManager->registerNode(playerName = new entity("Selection Name"));
    playerName->setCurrentAnimation(players.at(0)->getNameAnimation());

    // Current Selection
    nodesManager->registerNode(currentSelection = new entity("Current Selection"));

    // Get selection arrow animations
    selectionOn = animationsManager->getAnimation("Selection Arrow On");
    selectionOff = animationsManager->getAnimation("Selection Arrow Off");
    leftArrowAnimation = rightArrowAnimation = selectionOff;

    // Setup player 1 controller
    player1Controller.setLeftCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::a);  });
    player1Controller.setRightCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::d);  });
    player1Controller.setDownCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::s);  });

    player1Controller.setLightCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::g);  });
    player1Controller.setJumpCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::w);  });

    globalSettings->player1Controller = player1Controller;

    // Setup player 2 controller
    player2Controller.setLeftCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::left);  });
    player2Controller.setRightCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::right);  });
    player2Controller.setDownCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::down);  });

    player2Controller.setLightCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::dot);  });
    player2Controller.setJumpCallback([this]() { return keyboardHandler->isKeyActive(keyboardHandler::key::up);  });

    globalSettings->player2Controller = player2Controller;

    currentController = &player1Controller;
}

void gameSelection::setup()
{
    // Reset players
    if (globalSettings->player1 != nullptr && nodesManager->hasChild(globalSettings->player1->getName()))
        nodesManager->removeChild(globalSettings->player1->getName());
    if (globalSettings->player2 != nullptr && nodesManager->hasChild(globalSettings->player2->getName()))
        nodesManager->removeChild(globalSettings->player2->getName());

    // Load animations
    for (players::genericPlayer* player : players)
    {
        player->getIntroAnimation()->load();
        player->getNameAnimation()->load();
    }
    for (maps::genericBackground* map : maps)
    {
        map->getIntroAnimation()->load();
        map->getNameAnimation()->load();
    }

    for (players::genericPlayer* p : players)
        p->setSelected(false);

    selectionFrame->getCurrentAnimation()->load();

    selectionOn->load();
    selectionOff->load();

    currentAnimation = players.at(0)->getIntroAnimation();

    option = 0;
    counter = 0;
    playerCount = 1;
    options = players.size();
    playersSelected = false;
    buttonPressed = false;

    globalSettings->background = nullptr;
    globalSettings->player1 = nullptr;
    globalSettings->player2 = nullptr;

    // Cleare render and set background color
    setBackgroundColor(255, 255, 255, 255);
}

void gameSelection::update(size_t delta)
{
    if (!playersSelected && players.at(option)->getSelected())
    {
        incrementOption();
        currentAnimation = players.at(option)->getIntroAnimation();
    }

    int playerNameWidthHalf = playerName->getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth()/2;

    // Setup animations
    selectionFrame->setConstraints(0, getWindowWidth(), 0, getWindowHeight());
    selectionArrow->setConstraints(0, getWindowWidth(), 0, getWindowHeight());
    playerName->setConstraints(0, getWindowWidth(), 0, getWindowHeight());
    currentSelection->setConstraints(0, getWindowWidth(), 0, getWindowHeight());

    selectionFrame->getCurrentAnimation()->setSpritesSize(600, 600);
    selectionFrame->centerToScreen(getWindowWidth(), getWindowHeight());
    selectionFrame->getCoordinates()->moveVertically(-100);

    // Setup current selection
    currentSelection->setCurrentAnimation(currentAnimation);
    currentSelection->setCoordinates(selectionFrame->getCoordinates());

    graphics::sprite
        *frameSprite = selectionFrame->getCurrentAnimation()->getCurrentFrame()->getSprite(),
        *currentSprite = currentSelection->getCurrentAnimation()->getCurrentFrame()->getSprite();
    currentSelection->getCoordinates()->moveHorizontally(frameSprite->getWidth() / 2 - currentSprite->getWidth()/2);
    currentSelection->getCoordinates()->moveVertically(frameSprite->getHeight() / 2 - currentSprite->getHeight() / 2);

    // Move player name
    playerName->setCurrentAnimation(players.at(option)->getNameAnimation());
    playerName->centerToScreen(getWindowWidth(), getWindowHeight());
    playerName->getCoordinates()->moveVertically(280);

    // Place selection arrows around player name
    selectionArrow->setCurrentAnimation(leftArrowAnimation);
    selectionArrow->getCurrentAnimation()->flipSprites(graphics::sprite::flip::none);
    selectionArrow->setCoordinates(playerName->getCoordinates());
    selectionArrow->getCoordinates()->moveHorizontally(-playerNameWidthHalf + 25);
    selectionArrow->update(delta);

    selectionArrow->setCurrentAnimation(rightArrowAnimation);
    selectionArrow->getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);
    selectionArrow->setCoordinates(playerName->getCoordinates());
    selectionArrow->getCoordinates()->moveHorizontally(playerNameWidthHalf - 25);
    selectionArrow->update(delta);

    // Handle player input
    if (!buttonPressed)
    {
        if (currentController->leftPressed())
        {
            decrementOption();
            leftArrowAnimation = selectionOn;
            buttonPressed = true;
        }
        else
            leftArrowAnimation = selectionOff;

        if(currentController->rightPressed())
        {
            incrementOption();
            buttonPressed = true;
            rightArrowAnimation = selectionOn;
        }
        else
            rightArrowAnimation = selectionOff;

        if (keyboardHandler->isKeyActive(keyboardHandler::key::q))
            shouldClose(true);
        
        if (currentController->lightPressed())
        {
            entities::player** player = nullptr;
            if (*(player = &globalSettings->player1) == nullptr || *(player = &globalSettings->player2) == nullptr)
            {
                nodesManager->registerNode(*player = players.at(option)->createPlayer("Player " + std::to_string(playerCount++)));
                players.at(option)->setSelected(true);
                buttonPressed = true;

                currentController = &globalSettings->player2Controller;

                if (globalSettings->player2 != nullptr)
                {
                    option = 0;
                    options = maps.size();
                    playersSelected = true;
                    currentAnimation = maps.at(option)->getIntroAnimation();

                    currentController = &globalSettings->player1Controller;
                }
            }
            else
            {
                globalSettings->background = maps.at(option)->getBackground();
                globalSettings->floorHeight = maps.at(option)->getFloorHeight();
                viewsManager->setActiveView("Map");
            }

            rightArrowAnimation = selectionOn;
            leftArrowAnimation = selectionOn;
        }

        if (buttonPressed)
        {
            if (!playersSelected)
                currentAnimation = players.at(option)->getIntroAnimation();
            else
                currentAnimation = maps.at(option)->getIntroAnimation();
        }
    }
    else
        buttonPressed = currentController->leftPressed() || currentController->rightPressed() || currentController->lightPressed();

    // Update animations
    selectionFrame->update(delta);
    playerName->update(delta);
    currentSelection->update(delta);
}

void gameSelection::cleannup()
{
    // Unload sprites
    for (players::genericPlayer* player : players)
        player->getIntroAnimation()->unload();

    selectionFrame->getCurrentAnimation()->unload();
    selectionArrow->getCurrentAnimation()->unload();
    playerName->getCurrentAnimation()->unload();
}