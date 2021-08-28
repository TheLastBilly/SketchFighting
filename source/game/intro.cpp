#include "views/intro.hpp"

#include "engine/inputs.hpp"
#include "utilities/logger.hpp"

using namespace ksf::views;

using namespace graphics;
using namespace engine;

register_logger()

void intro::initialize()
{
    animationManagerPtr = getRoot()->getChild<engine::managers::animationsManager>("Animations Manager");
    collisionManagerPtr = getRoot()->getChild<engine::managers::collisionsManager>("Collisions Manager");

    idleAnimation = animationManagerPtr->getChild<graphics::animation>("standing");
    walkingAnimation = animationManagerPtr->getChild<graphics::animation>("walking");
    jumpingAnimation = animationManagerPtr->getChild<graphics::animation>("jumping");

    idleAnimation->load();
    walkingAnimation->load();
    jumpingAnimation->load();

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        backgroundPtr = new entities::background("Background", backgroundAnimation = animationManagerPtr->getAnimation("background"))
    );
    backgroundAnimation->load();

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        floorPtr = new entities::floor("Floor", getWindowWidth(), 1, 0, getWindowHeight()-10)
    );

    idleAnimation->setSpritesSize(200, 200);
    walkingAnimation->setSpritesSize(200, 200);
    jumpingAnimation->setSpritesSize(200, 200);

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        playerPtr = new entities::player("Player", idleAnimation, walkingAnimation, jumpingAnimation)
    );

    idleAnimation = animationManagerPtr->getChild<graphics::animation>("standing2");
    walkingAnimation = animationManagerPtr->getChild<graphics::animation>("walking2");
    jumpingAnimation = animationManagerPtr->getChild<graphics::animation>("jumping2");

    idleAnimation->setSpritesSize(200, 200);
    walkingAnimation->setSpritesSize(200, 200);
    jumpingAnimation->setSpritesSize(200, 200);

    getRoot()->getChild<managers::nodesManager>("Generic Nodes Manager")->registerNode(
        player2Ptr = new entities::player("Player2", idleAnimation, walkingAnimation, jumpingAnimation)
    );

    playerPtr->setGravity(.02);
    playerPtr->setHorizontalSpeed(.3);
    playerPtr->setJumpSpeed(10.);

    player2Ptr->setGravity(.02);
    player2Ptr->setHorizontalSpeed(.3);
    player2Ptr->setJumpSpeed(10.);

    keyboardHandlerPtr = getRoot()->getChild<engine::keyboardHandler>("Keyboard Handler");

    backgroundPtr->getCurrentAnimation()->setSpritesSize(getWindowWidth(), getWindowHeight());
    backgroundPtr->centerToScreen(getWindowWidth(), getWindowHeight());
        

    entities::player::controller controller;
    controller.setLeftCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::left);  });
    controller.setRightCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::right);  });
    controller.setUpCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::up);  });
    controller.setDownCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::down);  });

    controller.setLightCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::z);  });
    controller.setHeavyCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::x);  });
    controller.setJumpCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::space);  });
    playerPtr->setController(controller);

    controller.setLeftCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::a);  });
    controller.setRightCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::d);  });
    controller.setUpCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::w);  });
    controller.setDownCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::s);  });

    controller.setLightCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::g);  });
    controller.setHeavyCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::h);  });
    controller.setJumpCallback([this]() { return keyboardHandlerPtr->isKeyActive(keyboardHandler::key::f);  });
    player2Ptr->setController(controller);

    collisionManagerPtr->regsiterCollisionEvent(
        new engine::managers::collisionEvent("player1hitsfloor", playerPtr, floorPtr, [=]() { playerPtr->setMidAir(false); }, [=]() { playerPtr->setMidAir(true); })
    );
    collisionManagerPtr->regsiterCollisionEvent(
        new engine::managers::collisionEvent("player2hitsfloor", player2Ptr, floorPtr, [=]() { player2Ptr->setMidAir(false); }, [=]() { player2Ptr->setMidAir(true); })
    );

    playerPtr->setVerticalContraints(0, floorPtr->getCoordinates()->getUpperLimit());
    player2Ptr->setVerticalContraints(0, floorPtr->getCoordinates()->getUpperLimit());
}

void intro::setup()
{
    SDL_SetRenderDrawColor(getRenderer(), 255,255,255,255);
    SDL_RenderClear(getRenderer());

    collisionManagerPtr->getCollision("player1hitsfloor")->setActive(true);
    collisionManagerPtr->getCollision("player2hitsfloor")->setActive(true);
}

void intro::cleannup()
{
    idleAnimation->unload();
    walkingAnimation->unload();
    jumpingAnimation->unload();
    backgroundAnimation->unload();
}

void intro::update(size_t delta)
{
    if (keyboardHandlerPtr->isKeyActive(engine::keyboardHandler::q))
        shouldClose(true);

    playerPtr->setFloorHeight(floorPtr->getCoordinates()->getY());
    player2Ptr->setFloorHeight(floorPtr->getCoordinates()->getY());
    playerPtr->setWindowBorders(0, getWindowWidth());
    player2Ptr->setWindowBorders(0, getWindowWidth());

    playerPtr->update(delta);
    player2Ptr->update(delta);

    backgroundPtr->update(delta);
}