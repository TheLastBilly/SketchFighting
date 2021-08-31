#include "engine/engine/core.hpp"

#include "utilities/loader.hpp"

#include "entities/globalSettings.hpp"

#include "views/mainMenu.hpp"
#include "views/fadingView.hpp"
#include "views/gameSelection.hpp"
#include "views/map.hpp"

#define APP_NAME "King Sketch Figthing"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

void setupCore(engine::core *engineCore)
{
    engineCore->setWindowHeight(720);
    engineCore->setWindowWidth(1080);

#ifdef _DEBUG
    engineCore->setAssetsRootPath(std::string(DEBUG_ASSETS_PATH));
#else
    engineCore->setAssetsRootPath(std::string(SDL_GetBasePath()) + "assets");
#endif

    engineCore->getNodesManager()->registerNode( new ksf::entities::globalSettings() );

    ksf::utilities::contentLoader::loadSprites(engineCore->getAssetsManager());
    ksf::utilities::contentLoader::loadAnimations(engineCore->getAnimationsManager(), engineCore->getAssetsManager());

    engineCore->getViewsManager()->registerView(new ksf::views::mainMenu());
    engineCore->getViewsManager()->registerView(new ksf::views::fadingView("Instructions", "Instructions", 600, 600, 5000, "Game Selection"));
    engineCore->getViewsManager()->registerView(new ksf::views::fadingView("Credits", "Credits", 600, 600, 5000, "Main Menu"));
    engineCore->getViewsManager()->registerView(new ksf::views::gameSelection());
    engineCore->getViewsManager()->registerView(new ksf::views::map());

    engineCore->getViewsManager()->setActiveView("Credits");
    
    engineCore->setAppName(APP_NAME);
}