#ifndef ICONFIG_HPP
#define ICONFIG_HPP

#include <bitset>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>

#define pEnum(x) CUtility::GetEnumName<>(x)

#define logFunc std::cout << __func__ << std::endl;

namespace Evolution
{
    using Resolution = float;
    using NFResolution32 = int32_t;
    using NFResolution16 = int16_t;

    using shortBool = std::bitset<1>;

    namespace Nutrition
    {
        constexpr auto PROTEIN = 0.4;
        constexpr auto CARBON = 0.4;
        constexpr auto FAT = 0.4;
        constexpr auto WATER = 0.4;
    }

    namespace Stamina
    {
        constexpr auto PROTEIN = 0.2;
        constexpr auto CARBON = 0.05;
        constexpr auto FAT = 0.05;
        constexpr auto WATER = 0.7;
    }

    namespace Manager
    {
        using Priority = Resolution;
        using EntityId = NFResolution32;
        constexpr auto OrganismCount = 5;
        constexpr auto CarnivoreCount = 1;
        constexpr auto HerbivoreCount = 30;
        constexpr auto OmnivoreCount = 0;
        constexpr auto InvalidEntityId = -1;
    }
    namespace Utility
    {
        constexpr auto Height = 800;
        constexpr auto FrameLimit = 120;
        constexpr auto Width = 800;
        constexpr auto WindowName = "EVOLUTION";
        constexpr auto Pi = 3.147;
        constexpr auto TotalAngle = 360;
        constexpr auto TotalHemisphere = 2;
        constexpr auto TotalQuadrant = 4;
        constexpr auto TotalProbability = 100;
        constexpr auto ProbabilityFor = 70;
        constexpr auto ProbabilityAgainst = 30;
        constexpr auto MaxColorVal = 254;
        constexpr auto StepReductionFactor = 1;
        constexpr auto SpeedReductionFactor = 1;
        constexpr auto SpeedEnhancementFactor = 1;
        constexpr auto ConeWidth = 1;
        const auto ConeColor = sf::Color::White;
        constexpr auto LabelSize = 20;
        const auto LabelColor = sf::Color::Black;
        constexpr auto FontPath = "../resource/font/FUTRFW.TTF";

        enum Quadrant : uint8_t
        {
            FIRST = 0,
            SECOND = 1,
            THIRD = 2,
            FOURTH = 3
        };

        enum Hemisphere : int8_t
        {
            UPPER = 1,
            LOWER = -1
        };

        enum Choice : uint8_t
        {
            HEADS = 0,
            TAILS
        };
    }

    namespace Movement
    {
        constexpr auto MinSteps = 60;
        constexpr auto MaxSteps = 100;
        enum class MovementType : uint8_t
        {
            Randomly = 0,
            Purposely = 1,
            Chase = 2
        };

        enum class MovementOperation : uint8_t
        {
            INVALID = 254,
            IncrementSpeed = 0,
            DecrementSpeed,
            RotateBy180,
            RotateBy90 = 3,
            RotateByRandom,
            ChangeMotionToKill,
            ChangeMotionToGroup,
            ChangeMotionToIgnore = 7,
            ChangeMotionToFight,
            ChangeMotionToRun,
        };

        struct MovementAttribute
        {
            std::vector<Movement::MovementOperation> operations;
            Manager::EntityId targetId;
            Resolution offset;
        };

        using Operations = MovementAttribute;
    }

    namespace Position
    {
        constexpr auto MIN_VALUE = 300;
        constexpr auto MAX_VALUE = 700;

        constexpr auto MIN_OFFSET = 30;
        constexpr auto MAX_OFFSET = 300;
    }

    namespace General
    {
        constexpr auto MIN_POPULATION = 1;
        constexpr auto MAX_POPULATION = 20;
    }

    namespace Organism
    {
        enum class OrganismType : uint8_t
        {
            INVALID = 254,
            HERBIVORE = 0,
            CARNIVORE = 1,
            OMNIVORE = 2
        };

        struct Attributes
        {
            Resolution speed{0};
            Resolution visionConeAngle{0};
            Resolution visionDepth{0};
            Resolution stamina{0};
            Resolution energy{0};
            Resolution socializing{0};
            Resolution aggression{0};
            NFResolution32 id;
            sf::Vector2f position;

            OrganismType type;
            sf::Text label;
        };

        // Behaviours
        constexpr auto MinPriorityToFight = 30;
        constexpr auto MinThresholdEnergy = 20;
        constexpr auto MaxThresholdEnergy = 90;
        constexpr auto MinThresholdStamina = 50;
        constexpr auto MinThresholdAggression = 60;

        constexpr auto MaxSpawnEnergy = 50;
        constexpr auto MinSpawnEnergy = 0;
        constexpr auto CarnivoreEnergyOffset = 50;
        constexpr auto HerbivoreEnergyOffset = 20;
        constexpr auto OmnivoreEnergyOffset = 35;

        constexpr auto MaxSpawnStamina = 50;
        constexpr auto MinSpawnStamina = 0;
        constexpr auto CarnivoreStaminaOffset = 20;
        constexpr auto HerbivoreStaminaOffset = 50;
        constexpr auto OmnivoreStaminaOffset = 35;

        constexpr auto MaxSpawnConeAngle = 90;
        constexpr auto MinSpawnConeAngle = 45;
        constexpr auto CarnivoreConeAngleOffset = 30;
        constexpr auto HerbivoreConeAngleOffset = 50;
        constexpr auto OmnivoreConeAngleOffset = 15;

        constexpr auto MaxSpawnConeDepth = 100;
        constexpr auto MinSpawnConeDepth = 50;
        constexpr auto CarnivoreConeDepthOffset = 0;
        constexpr auto HerbivoreConeDepthOffset = 50;
        constexpr auto OmnivoreConeDepthOffset = 15;

        constexpr auto MaxSpawnSpeed = 50;
        constexpr auto MinSpawnSpeed = 0;
        constexpr auto CarnivoreSpeedOffset = 30;
        constexpr auto HerbivoreSpeedOffset = 50;
        constexpr auto OmnivoreSpeedOffset = 25;

        constexpr auto MaxSpawnAggression = 50;
        constexpr auto MinSpawnAggression = 0;
        constexpr auto CarnivoreAggressionOffset = 50;
        constexpr auto HerbivoreAggressionOffset = 10;
        constexpr auto OmnivoreAggressionOffset = 30;

        constexpr auto MinEdges = 3;
        constexpr auto MaxEdges = 10;
        constexpr auto MinRadius = 5;
        constexpr auto MaxRadius = 10;
        const sf::Color SpawnColor = sf::Color::White;
        const sf::Color CarnivoreSpawnColor = sf::Color::Red;
        const sf::Color HerbivoreSpawnColor = sf::Color::Green;
        const sf::Color OmnivoreSpawnColor = sf::Color::Yellow;
    }

    namespace Behaviour
    {
        enum class ReactionType : uint8_t
        {
            INVALID = 254,
            KILL = 0,
            IGNORE = 1,
            RUN = 2,
            FIGHT = 3,
            GROUP = 4,
            EAT = 5
        };

        using ReactionCb = std::function<void(Movement::Operations)>;
    }

}

#endif