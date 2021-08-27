#include "engine/engine/core.hpp"

#include "views/intro.hpp"
#include "utilities/loader.hpp"

#define APP_NAME "King Sketch Figthing"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

void setupCore(engine::core *engineCore)
{
    engineCore->setWindowHeight(720);
    engineCore->setWindowWidth(1080);

    engineCore->setAssetsRootPath("C:\\Users\\joset\\Documents\\SketchFighting\\assets\\export");

    ksf::utilities::loader::loadSprites(engineCore->getAssetsManager());
    ksf::utilities::loader::loadAnimations(engineCore->getAnimationsManager(), engineCore->getAssetsManager());

    engineCore->getViewsManager()->registerView(new ksf::views::intro());
    engineCore->getViewsManager()->setActiveView("Intro");
    
    engineCore->setAppName(APP_NAME);
}