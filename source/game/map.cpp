#include "views/map.hpp"

#include "engine/inputs.hpp"
#include "utilities/logger.hpp"

#include "engine/managers/collisionsManager.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger()

static inline int clampHealth(int health)
{
    return health >= 0 ? (health <= 100 ? health : 100) : 0;
}

void map::initialize()
{
    collisionsManager = getRoot()->getChild<engine::managers::collisionsManager>("Collisions Manager");
    nodesManager = getRoot()->getChild<engine::managers::nodesManager>("Generic Nodes Manager");
    animationsManager = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    viewsManager = getRoot()->getChild<engine::managers::viewsManager>("Views Manager");

    nodesManager->registerNode(pencilOk = new entity("Pencil Ok"));
    nodesManager->registerNode(pencilBad = new entity("Pencil Bad"));
    nodesManager->registerNode(circle = new entity("Player Circle"));
    nodesManager->registerNode(p1 = new entity("P1"));
    nodesManager->registerNode(p2 = new entity("P2"));
    nodesManager->registerNode(wins = new entity("Wins"));

    pencilOk->setCurrentAnimation(animationsManager->getAnimation("UI Pencil Ok"));
    pencilBad->setCurrentAnimation(animationsManager->getAnimation("UI Pencil Bad"));
    circle->setCurrentAnimation(animationsManager->getAnimation("UI Circle"));
    p1->setCurrentAnimation(animationsManager->getAnimation("UI P1"));
    p2->setCurrentAnimation(animationsManager->getAnimation("UI P2"));

    p1Wins = animationsManager->getAnimation("UI P1 Wins");
    p2Wins = animationsManager->getAnimation("UI P2 Wins");
}

void map::setup()
{
    // Get global settings
    globalSettings = nodesManager->getChild<entities::globalSettings>("Global Settings");

    // Get pointers from global settings
    nodesManager->registerNode(
        backgroundPtr = new background("Background", globalSettings->background)
    );

    player1Ptr = globalSettings->player1;
    player2Ptr = globalSettings->player2;

    // Load animations and assets
    player1Ptr->load();
    player2Ptr->load();
    backgroundPtr->load();
    p1Wins->load();
    p2Wins->load();
    pencilOk->getCurrentAnimation()->load();
    pencilBad->getCurrentAnimation()->load();
    circle->getCurrentAnimation()->load();
    p1->getCurrentAnimation()->load();
    p2->getCurrentAnimation()->load();

    // Set up oponents
    player1Ptr->setOponent(player2Ptr);
    player2Ptr->setOponent(player1Ptr);

    // Set up widgets
    p1->getCurrentAnimation()->setSpritesSize(100, 100);
    p2->getCurrentAnimation()->setSpritesSize(100, 100);
    circle->getCurrentAnimation()->setSpritesSize(100, 100);

    // Regsiter collisions
    collisionsManager->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Players are touching", player1Ptr, player2Ptr,
            collisionEventCallback{
                player1Ptr->setTouchingOponent(true);
                player2Ptr->setTouchingOponent(true);
            },
            collisionEventCallback{
                player1Ptr->setTouchingOponent(false);
                player2Ptr->setTouchingOponent(false);
            }
    ));
    collisionsManager->setAllCollisionsEnable(true);

    // Make sure players are facing eachother
    player1Ptr->getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);

    // Move players to their respective positions
    player1Ptr->getCoordinates()->setX(-getWindowWidth());
    player2Ptr->getCoordinates()->setX(getWindowWidth());
    player1Ptr->getCoordinates()->setY(getWindowHeight());
    player2Ptr->getCoordinates()->setY(getWindowHeight());

    // Assign player controllers
    player1Ptr->setController(globalSettings->player1Controller);
    player2Ptr->setController(globalSettings->player2Controller);

    // Set current wins animation
    wins->setCurrentAnimation(nullptr);

    initialScaling = true;
    victoryTimeCounter = 0;

    // Set background color
    setBackgroundColor(255,255,255,255);
}

void map::update(size_t delta)
{
    if (wins->getCurrentAnimation() != nullptr)
    {
        // Fuck it, just update the damn thing if someone won
        wins->centerToScreen(getWindowWidth(), getWindowHeight());

        player1Ptr->setPaused(true);
        player2Ptr->setPaused(true);

        if (victoryTimeCounter < victoryAnimationDelay)
            victoryTimeCounter += delta;
        else
            viewsManager->setActiveView("Game Selection");
    }

    // Setup background
    backgroundPtr->getCurrentAnimation()->setSpritesSize(getWindowWidth(), getWindowHeight());
    backgroundPtr->centerToScreen(getWindowWidth(), getWindowHeight());

    // Set player boundaries
    if (initialScaling || windowSizeHasChanged())
    {
        initialScaling = false;

        fixScaling();
    }

    player1Ptr->setFloorHeight(getWindowHeight() - globalSettings->floorHeight);
    player2Ptr->setFloorHeight(getWindowHeight() - globalSettings->floorHeight);

    // Show player icons
    circle->setCoordinates(p1->getCoordinates());
    circle->update(delta);
    p1->update(delta);

    circle->setCoordinates(p2->getCoordinates());
    circle->update(delta);
    p2->update(delta);

    // Update health bar icons off-screen
    pencilOk->getCoordinates()->setX(windowWidth*2);
    pencilOk->update(delta);
    pencilBad->getCoordinates()->setX(windowWidth * 2);
    pencilBad->update(delta);

    // Show health for player 1
    int health = 0;
    health = clampHealth(player1Ptr->getHealth());
    entity* healthEntity = nullptr;
    for (int i = 0; i < healthBarLenght; i++)
    {
        if (health == 0 || i <= ((health / healthBarLenght) % healthBarLenght) -1)
            healthEntity = pencilBad;
        else
            healthEntity = pencilOk;

        healthEntity->setCoordinates(p1->getCoordinates());
        healthEntity->getCoordinates()->moveHorizontally((healthBarLenght - i) * 50 + 20);
        healthEntity->update(0);
    }

    // Show health for player 2
    health = clampHealth(player2Ptr->getHealth());
    for (int i = 0; i < healthBarLenght; i++)
    {
        if (health == 0 || i <= ((health / healthBarLenght) % healthBarLenght) - 1)
            healthEntity = pencilBad;
        else
            healthEntity = pencilOk;

        healthEntity->setCoordinates(p2->getCoordinates());
        healthEntity->getCoordinates()->moveHorizontally(-((healthBarLenght - i) * 50 + 20));
        healthEntity->update(0);
    }

    if (player1Ptr->getHealth() <= 0)
        wins->setCurrentAnimation(p2Wins);
    if (player2Ptr->getHealth() <= 0)
        wins->setCurrentAnimation(p1Wins);

    backgroundPtr->update(delta);
    player1Ptr->update(delta);
    player2Ptr->update(delta);
    wins->update(delta);
}

void map::cleannup()
{
    // Unload sprites
    pencilOk->getCurrentAnimation()->unload();
    pencilBad->getCurrentAnimation()->unload();
    circle->getCurrentAnimation()->unload();
    p1->getCurrentAnimation()->unload();
    p2->getCurrentAnimation()->unload();

    backgroundPtr->unload();
    player1Ptr->unload();
    player2Ptr->unload();

    p1Wins->unload();
    p2Wins->unload();

    // Remove collision events
    collisionsManager->removeChild("Players are touching");

    // Remove background
    nodesManager->removeChild("Background");
}

void map::fixScaling()
{
    windowWidth = getWindowWidth();
    windowHeight = getWindowHeight();

    player1Ptr->setWindowBorders(0, windowWidth);
    player2Ptr->setWindowBorders(0, windowWidth);

    pencilOk->setConstraintsBasedOnCurrentSprite(0, windowWidth, 0, windowHeight);
    pencilBad->setConstraintsBasedOnCurrentSprite(0, windowWidth, 0, windowHeight);
    circle->setConstraintsBasedOnCurrentSprite(0, windowWidth, 0, windowHeight);
    p1->setConstraintsBasedOnCurrentSprite(0, windowWidth, 0, windowHeight);
    p2->setConstraintsBasedOnCurrentSprite(0, windowWidth, 0, windowHeight);

    p1->getCoordinates()->moveHorizontally(-windowWidth);
    p1->getCoordinates()->moveVertically(-windowHeight);

    p2->getCoordinates()->moveHorizontally(windowWidth);
    p2->getCoordinates()->moveVertically(-windowHeight);
}