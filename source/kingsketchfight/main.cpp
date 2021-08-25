#include "engine/core.hpp"

#include "kingsketchfight/views/intro.hpp"
#include "kingsketchfight/utilities/loader.hpp"

void setupCore(engine::core *engineCore)
{
    engineCore->setAssetsRootPath("./test");

    ksf::utilities::loadSprites(engineCore->getAssetsManager());
    engineCore->getViewsManager()->registerView(new ksf::views::intro());
    engineCore->getViewsManager()->setActiveView("Intro");
    engineCore->setAppName(APP_NAME);
}