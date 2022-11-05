#include "CUtility.hpp"
#include "IConfig.hpp"
#include <iostream>
#include <map>
#include <math.h>
#include <random>

namespace Evolution
{
    std::shared_ptr<sf::RenderWindow> CUtility::m_windowPtr = nullptr;
    std::shared_ptr<sf::RenderWindow> CUtility::m_debugWindowPtr = nullptr;
    std::map<std::size_t, std::string> CUtility::m_enumTranslator{};
    sf::Font CUtility::m_font;

    void CUtility::Init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::RenderWindow> debugWindow)
    {
        m_windowPtr = window;
        m_debugWindowPtr = debugWindow;
        m_font.loadFromFile(Utility::FontPath);
    }

    Organism::Attributes CUtility::GenerateRandomAttributes(Organism::SpeciesType type)
    {

        Organism::Attributes attributes;
        attributes.energy = GetRandomValueInRange(Organism::MinSpawnEnergy, Organism::MaxSpawnEnergy);
        attributes.speed = GetRandomValueInRange(Organism::MinSpawnSpeed, Organism::MaxSpawnSpeed);
        attributes.speedbackup = attributes.speed;
        attributes.stamina = GetRandomValueInRange(Organism::MinSpawnStamina, Organism::MaxSpawnStamina);
        attributes.staminabackup = attributes.stamina;
        attributes.aggression = GetRandomValueInRange(Organism::MinSpawnAggression, Organism::MaxSpawnAggression);
        attributes.aggressionbackup = attributes.aggression;
        attributes.visionConeAngle = GetRandomValueInRange(Organism::MinSpawnConeAngle, Organism::MaxSpawnConeAngle);
        // attributes.visionConeAngle = 360;
        attributes.visionDepth = GetRandomValueInRange(Organism::MinSpawnConeDepth, Organism::MaxSpawnConeDepth);
        // attributes.visionDepth = 300;
        switch (type)
        {
        case Organism::SpeciesType::CARNIVORE:
        {
            GenerateRandomCarnivoreAttributes(attributes);
            break;
        }

        case Organism::SpeciesType::HERBIVORE:
        {
            GenerateRandomHerbivoreAttributes(attributes);
            break;
        }

        case Organism::SpeciesType::OMNIVORE:
        {
            GenerateRandomOmnivoreAttributes(attributes);
            break;
        }

        case Organism::SpeciesType::POI:
        {
            GenerateRandomPOIAttributes(attributes);
            break;
        }

        default:
            break;
        }
        return attributes;
    }

    void CUtility::GenerateRandomCarnivoreAttributes(Organism::Attributes &attributes)
    {
        attributes.energy += Organism::CarnivoreEnergyOffset;
        attributes.speed += Organism::CarnivoreSpeedOffset;
        attributes.stamina += Organism::CarnivoreStaminaOffset;
        attributes.aggression += Organism::CarnivoreAggressionOffset;
        attributes.visionConeAngle += Organism::CarnivoreConeAngleOffset;
        attributes.visionDepth += Organism::CarnivoreConeDepthOffset;
    }

    void CUtility::GenerateRandomHerbivoreAttributes(Organism::Attributes &attributes)
    {
        attributes.energy += Organism::HerbivoreEnergyOffset;
        attributes.speed += Organism::HerbivoreSpeedOffset;
        attributes.stamina += Organism::HerbivoreStaminaOffset;
        attributes.aggression += Organism::HerbivoreAggressionOffset;
        attributes.visionConeAngle += Organism::HerbivoreConeAngleOffset;
        attributes.visionDepth += Organism::HerbivoreConeDepthOffset;
    }

    void CUtility::GenerateRandomOmnivoreAttributes(Organism::Attributes &attributes)
    {
        attributes.energy += Organism::OmnivoreEnergyOffset;
        attributes.speed += Organism::OmnivoreSpeedOffset;
        attributes.stamina += Organism::OmnivoreStaminaOffset;
        attributes.aggression += Organism::OmnivoreAggressionOffset;
        attributes.visionConeAngle += Organism::OmnivoreConeAngleOffset;
        attributes.visionDepth += Organism::OmnivoreConeDepthOffset;
    }

    void CUtility::GenerateRandomPOIAttributes(Organism::Attributes &attributes)
    {
        switch (attributes.subType)
        {
        case Organism::SpeciesSubType::VEGETATION:
        {
            GenerateRandomHerbAttributes(attributes);
            break;
        }

        default:
            break;
        }
    }

    void CUtility::GenerateRandomHerbAttributes(Organism::Attributes &attributes)
    {
        attributes.energy += Organism::HerbEnergyOffset;
        attributes.speed += Organism::HerbSpeedOffset;
        attributes.stamina += Organism::HerbStaminaOffset;
        attributes.aggression += Organism::HerbAggressionOffset;
        attributes.visionConeAngle += Organism::HerbConeAngleOffset;
        attributes.visionDepth += Organism::HerbConeDepthOffset;
    }

    void CUtility::SetOriginToCenter(CEntityWrapper<sf::CircleShape> &entity)
    {
        entity.setOrigin(entity.getRadius(), entity.getRadius());
    }

    void CUtility::SetRandomSpawnStats(CEntityWrapper<sf::CircleShape> &entity, Organism::SpeciesType type)
    {
        entity.setPosition(GetRandomValueInRange(0, Utility::Width), GetRandomValueInRange(0, Utility::Height));
        entity.setPointCount(GetRandomValueInRange(Organism::MinEdges, Organism::MaxEdges));

        entity.setRadius(GetRandomValueInRange(Organism::MinRadius, Organism::MaxRadius));
        entity.setRotation(GetRandomValueInRange(0, Utility::TotalAngle));
        SetOriginToCenter(entity);

        switch (type)
        {
        case Organism::SpeciesType::CARNIVORE:
        {
            entity.setFillColor(Utility::ConfigParser::GetInstance().GetCarnivoreSpawnColor());
            break;
        }

        case Organism::SpeciesType::HERBIVORE:
        {
            entity.setFillColor(Utility::ConfigParser::GetInstance().GetHerbivoreSpawnColor());
            break;
        }

        case Organism::SpeciesType::OMNIVORE:
        {
            entity.setFillColor(Utility::ConfigParser::GetInstance().GetOmnivoreSpawnColor());
            break;
        }

        case Organism::SpeciesType::POI:
        {
            entity.setFillColor(Utility::ConfigParser::GetInstance().GetHerbSpawnColor());
            break;
        }

        default:
            break;
        }
    }

    Resolution CUtility::GetDistanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
    {
        return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
    }

    sf::Text CUtility::PrepareText(const std::string &str, sf::Color color, sf::Text::Style style, NFResolution16 size, bool setToCentre)
    {
        sf::Text text;
        text.setFillColor(color);
        text.setCharacterSize(size);
        text.setFont(m_font);
        text.setStyle(style);
        text.setString(str);
        sf::FloatRect textRect = text.getLocalBounds();
        if (setToCentre)
        {
            text.setOrigin(textRect.left + textRect.width / 2.0f,
                           textRect.top + textRect.height / 2.0f);
        }
        return text;
    }

    sf::Text CUtility::GenerateLabels(Manager::EntityId id)
    {
        return PrepareText(std::to_string(id), Utility::LabelColor, sf::Text::Style::Bold, Utility::LabelSize, true);
    }

    void CUtility::DisplayEntityStats(std::shared_ptr<CEntityWrapper<sf::CircleShape>> entity, std::string movementInfo)
    {
        if (entity == nullptr)
        {
            return;
        }
        auto resultStr = entity->ToString() + movementInfo;

        auto stats = PrepareText(resultStr, Utility::StatsKeyColor, sf::Text::Style::Bold, Utility::StatsSize, false);
        stats.setPosition({Utility::StatsXPos, Utility::StatsYPos});

        m_debugWindowPtr->draw(stats);
    }

    void CUtility::AddLabels(sf::Text &label, sf::Vector2f origin)
    {
        label.setPosition(origin);
        m_windowPtr->draw(label);
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
            tempCircle.setRadius(Utility::ConeWidth);
            tempCircle.setFillColor(Utility::ConeColor);
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

    Resolution CUtility::RadiansToDegree(Resolution radians)
    {
        return (radians / Utility::Pi) * (Utility::TotalAngle / 2);
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

    void CUtility::RegisterAllEnums()
    {
        using namespace Utility;
        RegisterEnum<Quadrant>(Quadrant::FIRST, "FIRST");
        RegisterEnum<Quadrant>(Quadrant::SECOND, "SECOND");
        RegisterEnum<Quadrant>(Quadrant::THIRD, "THIRD");
        RegisterEnum<Quadrant>(Quadrant::FOURTH, "FOURTH");

        RegisterEnum<Hemisphere>(Hemisphere::LOWER, "LOWER");
        RegisterEnum<Hemisphere>(Hemisphere::UPPER, "UPPER");

        RegisterEnum<Choice>(Choice::HEADS, "HEADS");
        RegisterEnum<Choice>(Choice::TAILS, "TAILS");

        using namespace Movement;
        RegisterEnum<MovementOperation>(MovementOperation::ChangeMotionToFight, "ChangeMotionToFight");
        RegisterEnum<MovementOperation>(MovementOperation::ChangeMotionToGroup, "ChangeMotionToGroup");
        RegisterEnum<MovementOperation>(MovementOperation::ChangeMotionToIgnore, "ChangeMotionToIgnore");
        RegisterEnum<MovementOperation>(MovementOperation::ChangeMotionToKill, "ChangeMotionToKill");
        RegisterEnum<MovementOperation>(MovementOperation::ChangeMotionToRun, "ChangeMotionToRun");
        RegisterEnum<MovementOperation>(MovementOperation::DecrementSpeed, "DecrementSpeed");
        RegisterEnum<MovementOperation>(MovementOperation::IncrementSpeed, "IncrementSpeed");
        RegisterEnum<MovementOperation>(MovementOperation::RotateBy180, "RotateBy180");
        RegisterEnum<MovementOperation>(MovementOperation::RotateBy90, "RotateBy90");
        RegisterEnum<MovementOperation>(MovementOperation::RotateByRandom, "RotateByRandom");

        RegisterEnum<MovementType>(MovementType::Purposely, "Purposely");
        RegisterEnum<MovementType>(MovementType::Randomly, "Randomly");
        RegisterEnum<MovementType>(MovementType::Chase, "Chase");

        using namespace Organism;
        RegisterEnum<SpeciesType>(SpeciesType::CARNIVORE, "CARNIVORE");
        RegisterEnum<SpeciesType>(SpeciesType::HERBIVORE, "HERBIVORE");
        RegisterEnum<SpeciesType>(SpeciesType::OMNIVORE, "OMNIVORE");
        RegisterEnum<SpeciesType>(SpeciesType::POI, "POI");

        RegisterEnum<SpeciesSubType>(SpeciesSubType::VEGETATION, "VEGETATION");

        using namespace Behaviour;
        RegisterEnum<ReactionType>(ReactionType::FIGHT, "FIGHT");
        RegisterEnum<ReactionType>(ReactionType::GROUP, "GROUP");
        RegisterEnum<ReactionType>(ReactionType::IGNORE, "IGNORE");
        RegisterEnum<ReactionType>(ReactionType::KILL, "KILL");
        RegisterEnum<ReactionType>(ReactionType::RUN, "RUN");
        RegisterEnum<ReactionType>(ReactionType::CONSUME, "EAT");
    }

    bool CUtility::IsInCircumference(CEntityWrapper<sf::CircleShape> &entity, sf::Vector2f point)
    {
        auto radius = entity.getRadius() * 2;
        auto entityPos = entity.getPosition();

        if (std::pow(point.x - entityPos.x, 2) + std::pow(point.y - entityPos.y, 2) <= std::pow(radius, 2))
        {
            return true;
        }
        return false;
    }

    Resolution CUtility::GetAngleBetweenPoits(sf::Vector2f p1, sf::Vector2f p2)
    {
        return RadiansToDegree((p2.y - p1.y) / (p2.x - p1.x));
    }

}
