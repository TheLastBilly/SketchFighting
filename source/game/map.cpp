#include "views/map.hpp"

#include "engine/inputs.hpp"
#include "utilities/logger.hpp"

#include "engine/managers/collisionsManager.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger()

void map::initialize()
{
    collisionsManager = getRoot()->getChild<engine::managers::collisionsManager>("Collisions Manager");
    nodesManager = getRoot()->getChild<engine::managers::nodesManager>("Generic Nodes Manager");
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

    // Initialize floor
    nodesManager->registerNode(
        floorPtr = new map::floor("Floor", getWindowWidth(), 1, 0, getWindowHeight() - globalSettings->floorHeight)
    );

    // Regsiter floor collisions
    collisionsManager->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Player 1 Hits Floor", player1Ptr, floorPtr, collisionEventCallback { player1Ptr->setMidAir(false); }, collisionEventCallback { player1Ptr->setMidAir(true); })
    );
    collisionsManager->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Player 2 Hits Floor", player2Ptr, floorPtr, collisionEventCallback { player2Ptr->setMidAir(false); }, collisionEventCallback { player2Ptr->setMidAir(true); })
    );

    // Make sure players are facing eachother
    player1Ptr->getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);

    // Fix scaling
    fixScaling();

    // Move players to their respective positions
    player1Ptr->getCoordinates()->moveHorizontally(-getWindowWidth());
    player1Ptr->getCoordinates()->moveVertically(getWindowHeight());
    player2Ptr->getCoordinates()->moveHorizontally(getWindowWidth());
    player2Ptr->getCoordinates()->moveVertically(getWindowHeight());

    // Assign player controllers
    player1Ptr->setController(globalSettings->player1Controller);
    player2Ptr->setController(globalSettings->player2Controller);

    initialScaling = true;

    // Set background color
    setBackgroundColor(255,255,255,255);
}

void map::update(size_t delta)
{
    // Setup background
    backgroundPtr->getCurrentAnimation()->setSpritesSize(getWindowWidth(), getWindowHeight());
    backgroundPtr->centerToScreen(getWindowWidth(), getWindowHeight());

    // Set player boundaries
    if (initialScaling || windowSizeHasChanged())
    {
        initialScaling = false;

        fixScaling();
    }

    player1Ptr->update(delta);
    player2Ptr->update(delta);

    backgroundPtr->update(delta);
}

void map::cleannup()
{
    // Unload sprites
    backgroundPtr->unload();
    player1Ptr->unload();
    player2Ptr->unload();

    // Remove collision events
    collisionsManager->removeChild("Player 1 Hits Floor");
    collisionsManager->removeChild("Player 2 Hits Floor");

    // Remove floor
    nodesManager->removeChild("Floor");

    // Remove background
    nodesManager->removeChild("Background");
}