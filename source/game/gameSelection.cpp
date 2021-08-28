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

    players::genericPlayer* player = nullptr;

    // Get players (loaders)
    nodesManager->registerNode(player = new players::hammerGuy(animationsManager));
    players.push_back(player);
    nodesManager->registerNode(player = new players::miso(animationsManager));
    players.push_back(player);

    // Register entities

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
    // Load animations
    for (players::genericPlayer* player : players)
    {
        player->getIdleAnimation()->load();
        player->getNameAnimation()->load();
    }

    selectionFrame->getCurrentAnimation()->load();

    selectionOn->load();
    selectionOff->load();

    // Setup animations
    selectionFrame->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);
    selectionArrow->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);
    playerName->setConstraints(0, getWindowWidth(), getWindowHeight(), 0);

    selectionFrame->getCurrentAnimation()->setSpritesSize(600,600);
    selectionFrame->centerToScreen(getWindowWidth(), getWindowHeight());
    selectionFrame->getCoordinates()->moveVertically(-100);

    option = 0;
    counter = 0;
    options = players.size();
    optionSelected = false;

    // Cleare render and set background color
    setBackgroundColor(255, 255, 255, 255);
}

void gameSelection::update(size_t delta)
{
    int playerNameWidthHalf = playerName->getCurrentAnimation()->getCurrentFrame()->getSprite()->getWidth()/2;

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
            option = option < 1 ? options - 1 : option-1;
            leftArrowAnimation = selectionOn;
            buttonPressed = true;
        }
        else
            leftArrowAnimation = selectionOff;

        if(currentController->rightPressed())
        {
            option = option >= options -1 ? 0 : option+1;
            buttonPressed = true;
            rightArrowAnimation = selectionOn;
        }
        else
            rightArrowAnimation = selectionOff;
    }
    buttonPressed = currentController->leftPressed() || currentController->rightPressed();

    // Update animations
    selectionFrame->update(delta);
    playerName->update(delta);
}

void gameSelection::cleannup()
{
    // Unload sprites
    for (players::genericPlayer* player : players)
        player->getIdleAnimation()->unload();

    selectionFrame->getCurrentAnimation()->unload();
    selectionArrow->getCurrentAnimation()->unload();
    playerName->getCurrentAnimation()->unload();
}