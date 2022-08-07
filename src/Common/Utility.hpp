#ifndef CUTILITY_CPP
#define CUTILITY_CPP

#include "IConfig.hpp"
#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Evolution
{

    class CUtility
    {
    public:
        static Resolution GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
        {
            return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
        }

        static Resolution GetRandomValueInRange(Resolution low, Resolution high)
        {
            std::random_device rd;  // Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
            std::uniform_int_distribution<Resolution> dis(low, high);

            return dis(gen);
        }

    private:
    };

}

#endif