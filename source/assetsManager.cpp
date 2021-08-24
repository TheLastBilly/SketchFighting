#include "engine/assetsManager.hpp"

register_logger();

#define validatePath(path)                                                                      \
    if(path.size() < 1)                                                                         \
        throw_exception_with_msg(utilities::invalid_path_error, "file path cannot be empty");   \
                                                                                                \
    if(path[path.size()-1] != '/')                                                              \
        path += "/";

#define loadSprite(basePath, name, path, renderer)                                              \
    sprites.push_back(std::make_shared<sprite>(name, basePath + path, renderer));               \
    appendChild(sprites.back());

using namespace engine;
using namespace graphics;

void assetsManager::loadSprites(std::string basePath, SDL_Renderer *renderer)
{
    validatePath(basePath);
    
    info("Loading sprites from \"" + basePath + "\"");
    while(!spriteQueue.empty())
    {
        std::pair<std::string, std::string> pair = spriteQueue.front();
        loadSprite(basePath, pair.first, pair.second, renderer);
        spriteQueue.pop();
    }
    info("Done loading sprites from \"" + basePath + "\"");
}