#include <vector>
#include <utility>

#include "kingsketchfight/utilities/loader.hpp"

void ksf::utilities::loadSprites(engine::assetsManager* manager)
{
    std::vector<std::pair<std::string, std::string>> sprites =
    {
        {"Test", "Test.png"}
    };

    for(const auto &sprite: sprites)
        manager->requestSprite(sprite.first, sprite.second);
}