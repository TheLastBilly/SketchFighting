#include <vector>
#include <utility>

#include "utilities/loader.hpp"
#include "utilities/logger.hpp"

register_logger()

using namespace ksf::utilities;

void loader::loadSprites(engine::managers::assetsManager* manager)
{
    const std::vector<std::pair<std::string, std::string>> sprites =
    {
        {"standing01", "standing01.png"},
        {"standing02", "standing02.png"},

        {"walking01", "walking01.png"},
        {"walking02", "walking02.png"},
        {"walking03", "walking03.png"},

        {"jumping01", "jumping01.png"},
        {"jumping02", "jumping02.png"},

        {"background01","beach/1.png"},
        {"background02","beach/2.png"},
        {"background03","beach/3.png"},
        {"background04","beach/4.png"},
        {"background05","beach/5.png"}
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

    animationsManagerPtr->requestAnimation("walking2", {
        {"walking01", 500},
        {"walking02", 500},
        {"walking03", 500},
        {"walking02", 500}
    });
    animationsManagerPtr->requestAnimation("standing2", {
        {"standing01", 700},
        {"standing02", 700},
    });
    animationsManagerPtr->requestAnimation("jumping2", {
        {"jumping01", 700},
        {"jumping02", 700},
    });

    animationsManagerPtr->requestAnimation("background", {
        {"background01", 500},
        {"background02", 500},
        {"background03", 500},
        {"background04", 500},
        {"background05", 500}
    });
}