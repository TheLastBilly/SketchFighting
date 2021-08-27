#include <vector>
#include <utility>

#include "utilities/loader.hpp"
#include "utilities/logger.hpp"

register_logger()

using namespace ksf::utilities;

void loader::loadSprites(engine::managers::assetsManager* manager)
{
    std::vector<std::pair<std::string, std::string>> sprites =
    {
        {"standing01", "standing01.png"},
        {"standing02", "standing02.png"},

        {"walking01", "walking01.png"},
        {"walking02", "walking02.png"},
        {"walking03", "walking03.png"},

        {"jumping01", "jumping01.png"},
        {"jumping02", "jumping02.png"}
    };

    for(const auto &sprite: sprites)
        manager->requestSprite(sprite.first, sprite.second);
}

void loader::loadAnimations(engine::managers::animationsManager* animationsManagerPtr, engine::managers::assetsManager* assetsManaterPtr)
{
    animationsManagerPtr->requestAnimation("walking",{
        {"walking01", 500},
        {"walking02", 500},
        {"walking03", 500},
        {"walking02", 500}
    });
    animationsManagerPtr->requestAnimation("standing", {
        {"standing01", 700},
        {"standing02", 700},
    });
    animationsManagerPtr->requestAnimation("jumping", {
        {"jumping01", 700},
        {"jumping02", 700},
    });
}