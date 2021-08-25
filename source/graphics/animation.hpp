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
        class frame
        {
        public:
            frame(const sprite* spritePtr, int duration): spritePtr(spritePtr), duration(duration) {}
            frame(const frame& f): spritePtr(f.spritePtr), duration(f.duration) {}

            inline sprite* getSprite() const
            { return (sprite*)spritePtr; }

            inline int getDuration() const
            { return duration; }
            inline void setDuration(int duration)
            { this->duration = duration; }
        
        private:
            const sprite* spritePtr = nullptr; 
            int duration = 0;
        };

    public:
        animation(const std::string &name): node(name) {}

        inline void addFrame(engine::managers::assetsManager* manager, const std::string &name, int duration)
        { frames.push_back(frame(manager->getChild<sprite>(name), duration)); }
        inline void addFrames(engine::managers::assetsManager* manager, const std::vector<std::pair<std::string, int>> &frames)
        { for(const auto& f: frames) addFrame(manager, f.first, f.second); }

        frame* getFrame(size_t i) const
        {
            if(i >= frames.size())
                throw_exception_without_msg(utilities::index_out_of_bounds_error);
            
            return (frame*)&frames.data()[i];
        }
        inline size_t getFrameCount() const
        { return frames.size(); }

        void reset()
        {
            timer = 0;
            currentFrame = 0;
        }

        void play(size_t delta, int x, int y)
        {
            if(frames.size() < 1)
                return;

            size_t counter = timer;
            if((timer += delta) >= frames[currentFrame].getDuration())
            {
                currentFrame = currentFrame < frames.size()-1 ? currentFrame + 1: 0;
                timer = 0;
            }

            timer += delta;
            frames[currentFrame].getSprite()->render(x, y);
        }

    private:
        std::vector<frame> frames;

        size_t timer = 0;
        size_t currentFrame = 0;
    };
}