#include "engine/engine/core.hpp"

#include "utilities/loader.hpp"

#include "entities/globalSettings.hpp"

#include "views/mainMenu.hpp"
#include "views/instructions.hpp"
#include "views/gameSelection.hpp"
#include "views/map.hpp"

#define APP_NAME "King Sketch Figthing"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

void setupCore(engine::core *engineCore)
{
    engineCore->setWindowHeight(720);
    engineCore->setWindowWidth(1080);

    engineCore->setAssetsRootPath("C:\\Users\\joset\\Documents\\SketchFighting\\assets\\export");

    engineCore->getNodesManager()->registerNode( new ksf::entities::globalSettings() );

    ksf::utilities::contentLoader::loadSprites(engineCore->getAssetsManager());
    ksf::utilities::contentLoader::loadAnimations(engineCore->getAnimationsManager(), engineCore->getAssetsManager());

    engineCore->getViewsManager()->registerView(new ksf::views::mainMenu());
    engineCore->getViewsManager()->registerView(new ksf::views::instructions());
    engineCore->getViewsManager()->registerView(new ksf::views::gameSelection());
    engineCore->getViewsManager()->registerView(new ksf::views::map());

    engineCore->getViewsManager()->setActiveView("Game Selection");
    
    engineCore->setAppName(APP_NAME);
}