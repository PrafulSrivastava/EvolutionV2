#ifndef CUTILITY_HPP
#define CUTILITY_HPP

#include "IConfig.hpp"
#include "IEntity.hpp"
#include <math.h>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Evolution
{
    class CUtility
    {
    public:
        static void Init(std::shared_ptr<sf::RenderWindow> window);
        static Resolution GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);
        static void ShowVisionInfo(Resolution depth, Resolution cone, sf::Vector2f origin, Resolution direction);
        static sf::Vector2f GetMovementRatio(Resolution direction);
        static Resolution DegreeToRadians(Resolution degree);
        static Utility::Quadrant GetQuadrant(Resolution degree);
        static sf::Color GetRandomColor();
        static NFResolution32 GetRandomValueInRange(NFResolution32 low, NFResolution32 high);
        static Organism::Attributes GenerateRandomAttributes(Organism::OrganismType);
        static void GenerateRandomCarnivoreAttributes(Organism::Attributes &);
        static void GenerateRandomHerbivoreAttributes(Organism::Attributes &);
        static void GenerateRandomOmnivoreAttributes(Organism::Attributes &);
        static void SetRandomSpawnStats(CEntityWrapper<sf::CircleShape> &, Organism::OrganismType);
        static void SetOriginToCenter(CEntityWrapper<sf::CircleShape> &);
        static Utility::Choice HeadsOrTails();
        static NFResolution16 GetProbability();

    private:
        static std::shared_ptr<sf::RenderWindow> m_windowPtr;
    };

}

#endif