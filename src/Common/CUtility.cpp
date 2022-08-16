#include "CUtility.hpp"
#include "IConfig.hpp"
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

    Organism::Attributes CUtility::GenerateRandomAttributes()
    {

        Organism::Attributes attributes;
        attributes.energy = GetRandomValueInRange(Organism::MinSpawnEnergy, Organism::MaxSpawnEnergy);
        attributes.speed = GetRandomValueInRange(Organism::MinSpawnSpeed, Organism::MaxSpawnSpeed);
        attributes.stamina = GetRandomValueInRange(Organism::MinSpawnStamina, Organism::MaxSpawnStamina);
        attributes.aggression = GetRandomValueInRange(Organism::MinSpawnAggression, Organism::MaxSpawnAggression);
        attributes.visionConeAngle = GetRandomValueInRange(Organism::MinSpawnConeAngle, Organism::MaxSpawnConeAngle);
        attributes.visionDepth = GetRandomValueInRange(Organism::MinSpawnConeDepth, Organism::MaxSpawnConeDepth);
        return attributes;
    }

    void CUtility::SetOriginToCenter(CEntityWrapper<sf::CircleShape> &entity)
    {
        entity.setOrigin(entity.getRadius(), entity.getRadius());
    }

    void CUtility::SetRandomSpawnStats(CEntityWrapper<sf::CircleShape> &entity)
    {
        entity.setPosition(GetRandomValueInRange(0, Utility::Width), GetRandomValueInRange(0, Utility::Height));
        entity.setPointCount(GetRandomValueInRange(Organism::MinEdges, Organism::MaxEdges));
        entity.setFillColor(Organism::SpawnColor);
        entity.setRadius(GetRandomValueInRange(Organism::MinRadius, Organism::MaxRadius));
        entity.setRotation(GetRandomValueInRange(0, Utility::TotalAngle));
        SetOriginToCenter(entity);
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

    Utility::Quadrant CUtility::GetQuadrant(Resolution degree)
    {
        if (degree >= 0 && degree < 90)
        {
            return Utility::Quadrant::FIRST;
        }
        else if (degree >= 90 && degree < 180)
        {
            return Utility::Quadrant::SECOND;
        }
        else if (degree >= 180 && degree < 270)
        {
            return Utility::Quadrant::THIRD;
        }
        else
        {
            return Utility::Quadrant::FOURTH;
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
        return sf::Color(GetRandomValueInRange(0, Utility::MaxColorVal), GetRandomValueInRange(0, Utility::MaxColorVal), GetRandomValueInRange(0, Utility::MaxColorVal), GetRandomValueInRange(0, Utility::MaxColorVal));
    }

    NFResolution32 CUtility::GetRandomValueInRange(NFResolution32 low, NFResolution32 high)
    {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<NFResolution32> dis(low, high - 1);

        return dis(gen);
    }

    Utility::Choice CUtility::HeadsOrTails()
    {
        return (GetRandomValueInRange(0, 2) == 0) ? Utility::Choice::HEADS : Utility::Choice::TAILS;
    }

    NFResolution16 CUtility::GetProbability()
    {
        return GetRandomValueInRange(0, Utility::TotalProbability);
    }
}
