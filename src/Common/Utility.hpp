#ifndef CUTILITY_CPP
#define CUTILITY_CPP

#include "IConfig.hpp"
#include <math.h>
#include <SFML/Graphics.hpp>

namespace Evolution
{

    class CUtility
    {
    public:
        static Resolution GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
        {
            return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
        }

    private:
    };

}

#endif