#pragma once

#include "engine/node.hpp"

namespace math
{
    class coordinates: public engine::node
    {
    public:
        coordinates(const std::string &name): node(name) {}

        inline void setHorizontalRange(int leftLimit, int rightLimit)
        {
            this->leftLimit = leftLimit;
            this->rightLimit = rightLimit;
        }
        inline void setVerticalRange(int upperLimit, int lowerLimit)
        {
            this->upperLimit = upperLimit;
            this->lowerLimit = lowerLimit;
        }

        void moveHorizontally(int amount)
        {
            x += amount;
            if(x > rightLimit)
                x = rightLimit;
            if(x < leftLimit)
                x = leftLimit;
        }
        void moveVertically(int amount)
        {
            y += amount;
            if(y > upperLimit)
                y = upperLimit;
            if(y < lowerLimit)
                y = lowerLimit;
        }

        inline int getX() const
        { return x; }
        inline int getY() const
        { return y; }

    private:
        int x = 0, y = 0;

        int leftLimit = 0, rightLimit = 0, upperLimit = 0, lowerLimit = 0;
    };
}