#include "CUtility.hpp"
#include <iostream>
#include <math.h>
#include <random>

namespace Evolution
{
    std::shared_ptr<sf::RenderWindow> CUtility::m_windowPtr = nullptr;

    void CUtility::Init(std::shared_ptr<sf::RenderWindow> window)
    {
        m_windowPtr = window;
    }

    Resolution CUtility::GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
    {
        return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
    }

    void CUtility::ShowVisionInfo(Resolution depth, Resolution cone, sf::Vector2f origin, Resolution direction)
    {
        std::vector<sf::Vector2f> pointsOnDiameter;

        auto quad = GetQuadrant(direction);
        Resolution xUpperBound, xLowerBound, yUpperBound, yLowerBound, thetaUpper, thetaLower;

        thetaLower = direction - (cone / 2);
        thetaUpper = direction + (cone / 2);

        for (Resolution theta = thetaLower; theta <= thetaUpper; theta++)
        {
            auto x = depth * std::cos(DegreeToRadians(theta));
            auto y = depth * std::sin(DegreeToRadians(theta));

            pointsOnDiameter.push_back({x + origin.x, y + origin.y});
        }

        for (auto point : pointsOnDiameter)
        {
            sf::CircleShape tempCircle;
            tempCircle.setPosition(point);
            tempCircle.setRadius(1);
            tempCircle.setFillColor(GetRandomColor());
            m_windowPtr->draw(tempCircle);
        }
    }

    Quadrant CUtility::GetQuadrant(Resolution degree)
    {
        if (degree >= 0 && degree < 90)
        {
            return Quadrant::FIRST;
        }
        else if (degree >= 90 && degree < 180)
        {
            return Quadrant::SECOND;
        }
        else if (degree >= 180 && degree < 270)
        {
            return Quadrant::THIRD;
        }
        else
        {
            return Quadrant::FOURTH;
        }
    }

    sf::Vector2f CUtility::GetMovementRatio(Resolution direction)
    {
        auto radians = DegreeToRadians(direction);
        return {std::cos(radians), std::sin(radians)};
    }

    Resolution CUtility::DegreeToRadians(Resolution degree)
    {
        return (degree * Utility::Pi) / (Utility::TotalAngle / 2);
    }

    sf::Color CUtility::GetRandomColor()
    {
        return sf::Color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
    }

    NFResolution CUtility::GetRandomValueInRange(NFResolution low, NFResolution high)
    {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<NFResolution> dis(low, high);

        return dis(gen);
    }
}
