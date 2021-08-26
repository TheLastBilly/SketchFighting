#include <vector>
#include <utility>

#include "utilities/loader.hpp"

using namespace ksf::utilities;

void loader::loadSprites(engine::managers::assetsManager* manager)
{
    std::vector<std::pair<std::string, std::string>> sprites =
    {
        {"Test", "Test.png"},
        {"Test2", "ghidra.png"}
    };

    for(const auto &sprite: sprites)
        manager->requestSprite(sprite.first, sprite.second);
}

void loader::loadAnimations(engine::managers::animationsManager* animationsManagerPtr, engine::managers::assetsManager* assetsManaterPtr)
{
    animationsManagerPtr->requestAnimation("IntroAnimation",{
        {"Test", 1000},
        {"Test2", 500},
        {"Test", 1000},
        {"Test2", 500},
        {"Test", 1000},
        {"Test2", 500},
        {"Test", 1000},
        {"Test2", 500},
        {"Test", 1000},
        {"Test2", 500}
    });
}