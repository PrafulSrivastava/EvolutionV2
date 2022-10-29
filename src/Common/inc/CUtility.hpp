#ifndef PMG_CUTILITY_HPP
#define PMG_CUTILITY_HPP

#include "IConfig.hpp"
#include "IEntity.hpp"
// #include "IMovement.hpp"
#include <math.h>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

// namespace Evolution::Manager
// {
//     class IMovement;
// }
namespace Evolution
{
    class CUtility
    {
    public:
        static void Init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::RenderWindow> debugWindow = nullptr);
        static Resolution GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);
        static void ShowVisionInfo(Resolution depth, Resolution cone, sf::Vector2f origin, Resolution direction);
        static sf::Vector2f GetMovementRatio(Resolution direction);
        static Resolution DegreeToRadians(Resolution degree);
        static Resolution RadiansToDegree(Resolution radians);
        static Resolution GetAngleBetweenPoits(sf::Vector2f p1, sf::Vector2f p2);
        static Utility::Quadrant GetQuadrant(Resolution degree);
        static sf::Color GetRandomColor();
        static NFResolution32 GetRandomValueInRange(NFResolution32 low, NFResolution32 high);
        static Organism::Attributes GenerateRandomAttributes(Organism::SpeciesType);
        static void GenerateRandomCarnivoreAttributes(Organism::Attributes &);
        static void GenerateRandomHerbivoreAttributes(Organism::Attributes &);
        static void GenerateRandomOmnivoreAttributes(Organism::Attributes &);
        static void GenerateRandomPOIAttributes(Organism::Attributes &);
        static void GenerateRandomHerbAttributes(Organism::Attributes &);
        static void SetRandomSpawnStats(CEntityWrapper<sf::CircleShape> &, Organism::SpeciesType);
        static void SetOriginToCenter(CEntityWrapper<sf::CircleShape> &);
        static bool IsInCircumference(CEntityWrapper<sf::CircleShape> &, sf::Vector2f);
        static Utility::Choice HeadsOrTails();
        static NFResolution16 GetProbability();
        static void RegisterAllEnums();
        template <typename T>
        static void RegisterEnum(T enumVal, std::string enumName)
        {
            std::string key = typeid(enumVal).name();
            key += static_cast<uint8_t>(enumVal);
            auto hash = std::hash<std::string>{}(key);
            m_enumTranslator[hash] = enumName;
        }

        template <typename T>
        static std::string GetEnumName(T enumVal)
        {
            std::string key = typeid(enumVal).name();
            key += static_cast<uint8_t>(enumVal);
            auto hash = std::hash<std::string>{}(key);

            return m_enumTranslator[hash];
        }

        static sf::Text PrepareText(const std::string &str, sf::Color, sf::Text::Style, NFResolution16, bool);
        static sf::Text GenerateLabels(Manager::EntityId);
        static void AddLabels(sf::Text &, sf::Vector2f);
        static void DisplayEntityStats(std::shared_ptr<CEntityWrapper<sf::CircleShape>>, std::string);

    private:
        static std::shared_ptr<sf::RenderWindow> m_windowPtr;
        static std::shared_ptr<sf::RenderWindow> m_debugWindowPtr;
        static std::map<std::size_t, std::string> m_enumTranslator;
        static sf::Font m_font;
    };

}

#endif