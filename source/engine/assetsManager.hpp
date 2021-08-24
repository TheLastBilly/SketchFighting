#pragma once

#include <utility>
#include <queue>

#include "utilities/generics.hpp"
#include "utilities/logger.hpp"

#include "engine/node.hpp"
#include "graphics/sprite.hpp"

namespace engine
{
    class assetsManager: public engine::node 
    {
    public:
        assetsManager(const std::string &name): node(name) {}

        inline void requestSprite(const std::string& name, const std::string &path)
        { spriteQueue.push(std::pair<std::string, std::string>(name, path)); }
        void loadSprites(std::string basePath, SDL_Renderer *renderer);
    
    private:
        std::queue<std::pair<std::string, std::string>> spriteQueue;
        std::vector<std::shared_ptr<graphics::sprite>> sprites;
    };
}