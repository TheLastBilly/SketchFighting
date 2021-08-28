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
        new background("Background", globalSettings->background)
    );

    player1Ptr = globalSettings->player1;
    player2Ptr = globalSettings->player2;

    // Initialize floor
    nodesManager->registerNode(
        floorPtr = new map::floor("Floor", getWindowWidth(), 1, 0, getWindowHeight() - globalSettings->floorHeight)
    );

    // Setup background
    backgroundPtr->getCurrentAnimation()->setSpritesSize(getWindowWidth(), getWindowHeight());
    backgroundPtr->centerToScreen(getWindowWidth(), getWindowHeight());

    // Regsiter floor collisions
    collisionsManager->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Player 1 Hits Floor", player1Ptr, floorPtr, collisionEventCallback { player1Ptr->setMidAir(false); }, collisionEventCallback { player1Ptr->setMidAir(true); })
    );
    collisionsManager->regsiterCollisionEvent(
        new engine::managers::collisionEvent("Player 2 Hits Floor", player2Ptr, floorPtr, collisionEventCallback { player2Ptr->setMidAir(false); }, collisionEventCallback { player2Ptr->setMidAir(true); })
    );

    // Set player boundaries
    player1Ptr->setWindowBorders(0, getWindowWidth());
    player2Ptr->setWindowBorders(0, getWindowWidth());
    player1Ptr->setFloorHeight(floorPtr->getCoordinates()->getY());
    player2Ptr->setFloorHeight(floorPtr->getCoordinates()->getY());

    // Move players to their respective positions
    player1Ptr->getCoordinates()->moveHorizontally(0);
    player1Ptr->getCoordinates()->moveVertically(getWindowHeight());
    player2Ptr->getCoordinates()->moveHorizontally(getWindowWidth());
    player1Ptr->getCoordinates()->moveVertically(getWindowHeight());

    // Make sure players are facing eachother
    player1Ptr->getCurrentAnimation()->flipSprites(graphics::sprite::flip::horizontal);

    // Assign player controllers
    player1Ptr->setController(globalSettings->player1Controller);
    player2Ptr->setController(globalSettings->player2Controller);

    // Set background color
    setBackgroundColor(255,255,255,255);
}

void map::update(size_t delta)
{
    player1Ptr->update(delta);
    player2Ptr->update(delta);

    backgroundPtr->update(delta);
}

void map::cleannup()
{
    // Unload sprites
    backgroundPtr->getCurrentAnimation()->unload();
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