#include "engine/engine/core.hpp"

#include "views/intro.hpp"
#include "utilities/loader.hpp"

void setupCore(engine::core *engineCore)
{
    engineCore->setAssetsRootPath("./test");

    ksf::utilities::loader::loadSprites(engineCore->getAssetsManager());
    ksf::utilities::loader::loadAnimations(engineCore->getAnimationsManager(), engineCore->getAssetsManager());

    engineCore->getViewsManager()->registerView(new ksf::views::intro());
    engineCore->getViewsManager()->setActiveView("Intro");
    
    engineCore->setAppName(APP_NAME);
}