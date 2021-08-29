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

    // Set up oponents
    player1Ptr->setOponent(player2Ptr);
    player2Ptr->setOponent(player1Ptr);

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

    player1Ptr->setFloorHeight(getWindowHeight() - globalSettings->floorHeight);
    player2Ptr->setFloorHeight(getWindowHeight() - globalSettings->floorHeight);

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
    collisionsManager->removeChild("Players are touching");

    // Remove floor
    nodesManager->removeChild("Floor");

    // Remove background
    nodesManager->removeChild("Background");
}