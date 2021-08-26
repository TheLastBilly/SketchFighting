#include "engine/managers/animationsManager.hpp"

register_logger();

#define loadAnimation(manager, name, frames)                                                \
{                                                                                           \
    animation* animationPtr = new animation(name);                                          \
    animationPtr->addFrames(manager, frames);                                               \
    registerElement(animationPtr);                                                          \
}

using namespace engine::managers;
using namespace graphics;

void animationsManager::loadAnimations(assetsManager* assetsManaterPtr)
{
    while(!animationQueue.empty())
    {
        const std::pair<std::string, framesRequest> &pair = animationQueue.front();
        loadAnimation(assetsManaterPtr, pair.first, pair.second);
        animationQueue.pop();
    }
}