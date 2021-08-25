#pragma once

#include <vector>
#include <utility>

#include "engine/node.hpp"
#include "engine/managers/assetsManager.hpp"

#include "graphics/sprite.hpp"

namespace graphics
{
    class animation: public engine::node
    {
    public:
        struct frame
        {sprite* spritePtr; int duration;};

    public:
        animation(const std::string &name): node(name) {}

        inline void addFrame(engine::managers::assetsManager* manager, const std::string &name, int duration)
        { frames.push_back({.spritePtr = manager->getChild<sprite>(name), .duration = duration}); }
        inline void addFrames(engine::managers::assetsManager* manager, const std::vector<std::pair<std::string, int>> &frames)
        { for(const auto& f: frames) addFrame(manager, f.first, f.second); }

        inline void resetTimer()
        { timer = 0; }

        void play(size_t delta, int x, int y)
        {
            if(frames.size() < 1)
                return;

            size_t counter = timer;
            if((timer += delta) >= frames[currentFrame].duration)
            {
                currentFrame = currentFrame < frames.size()-1 ? currentFrame + 1: 0;
                timer = 0;
            }

            timer += delta;
            frames[currentFrame].spritePtr->render(x, y);
        }

    private:
        std::vector<frame> frames;

        size_t timer = 0;
        size_t currentFrame = 0;
    };
}