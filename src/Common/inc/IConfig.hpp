#ifndef ICONFIG_HPP
#define ICONFIG_HPP

#include <bitset>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Logger.hpp"

#ifdef DEBUG_MODE
constexpr auto DebugMode = true;
#else
constexpr auto DebugMode = false;
#endif

#define Debug(cmd) \
    if (DebugMode) \
    {              \
        cmd;       \
    }

#define FuncName Log(Log::INFO, __func__)

#define pEnum(x) Evolution::CUtility::GetEnumName<>(x)

#define Log(args, ...) Evolution::Utility::Logger::Logging(args, __VA_ARGS__)
using Log = Evolution::Utility::LogLevel;

namespace Evolution
{
    using Resolution = float;
    using NFResolution32 = int32_t;
    using NFResolution16 = int16_t;

    using shortBool = std::bitset<1>;

    using NotifyAction = std::function<void()>;
    constexpr auto DefaultTime = 1;

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
        constexpr auto CarnivoreCount = 50;
        constexpr auto HerbivoreCount = 0;
        constexpr auto OmnivoreCount = 0;
        constexpr auto HerbCount = 0;
        constexpr auto InvalidEntityId = -1;

        class IMovement;
    }
    namespace Utility
    {
        constexpr auto Height = 600;
        constexpr auto Width = 800;
        constexpr auto HeightDebugWindow = 800;
        constexpr auto WidthDebugWindow = 800;
        constexpr auto StatsXPos = WidthDebugWindow / 4;
        constexpr auto StatsYPos = HeightDebugWindow / 4;
        constexpr auto FrameLimit = 120;
        constexpr auto WindowName = "Evolution";
        constexpr auto DebugWindowName = "DebugInfo";
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
        constexpr auto FontPath = "../resource/font/times.ttf";
        constexpr auto ConfigPath = "../config/Application.json";
        const auto StatsKeyColor = sf::Color::White;
        const auto StatsValFontColor = sf::Color::White;
        const auto HighlightColor = sf::Color::Cyan;
        constexpr auto HighlightBoundry = 2;
        constexpr auto StatsSize = 15;

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

        struct MovementInfo
        {
            Evolution::Movement::MovementType type;
            NFResolution16 steps;
            Utility::Hemisphere hemisphere;
            Utility::Quadrant quadrant;
            Manager::EntityId target{Manager::InvalidEntityId};
        };
        struct TargetMovementInfo
        {
            std::vector<Movement::MovementOperation> operations;
            Manager::EntityId targetId;
            Resolution offset;
        };
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
        enum class SpeciesType : uint8_t
        {
            INVALID = 254,
            HERBIVORE = 0,
            CARNIVORE = 1,
            OMNIVORE = 2,
            POI = 3
        };

        enum class SpeciesSubType : uint8_t
        {
            // PointOfInterest
            VEGETATION = 0,
        };

        enum class EnergyBand : uint8_t
        {
            INVALID = 254,
            LOW = 0,
            MEDIUM = 1,
            HIGH = 2
        };

        // Life Span
        constexpr auto LifeCounter = 1; // seconds

        // Behaviours
        constexpr auto MinPriorityToFight = 30;
        constexpr auto MinThresholdEnergy = 35;
        constexpr auto MaxThresholdEnergy = 80;
        constexpr auto MinThresholdStamina = 50;
        constexpr auto MinThresholdAggression = 60;

        // Energy
        constexpr auto MaxSpawnEnergy = 50;
        constexpr auto MinSpawnEnergy = 0;
        constexpr auto CarnivoreEnergyOffset = 50;
        constexpr auto HerbivoreEnergyOffset = 20;
        constexpr auto OmnivoreEnergyOffset = 35;
        constexpr auto HerbEnergyOffset = 40;

        // Stamina
        constexpr auto MaxSpawnStamina = 50;
        constexpr auto MinSpawnStamina = 0;
        constexpr auto CarnivoreStaminaOffset = 20;
        constexpr auto HerbivoreStaminaOffset = 50;
        constexpr auto OmnivoreStaminaOffset = 35;
        constexpr auto HerbStaminaOffset = 50;

        // Vision Angle
        constexpr auto MaxSpawnConeAngle = 90;
        constexpr auto MinSpawnConeAngle = 45;
        constexpr auto CarnivoreConeAngleOffset = 30;
        constexpr auto HerbivoreConeAngleOffset = 50;
        constexpr auto OmnivoreConeAngleOffset = 15;
        constexpr auto HerbConeAngleOffset = 0;

        // Vision Depth
        constexpr auto MaxSpawnConeDepth = 100;
        constexpr auto MinSpawnConeDepth = 50;
        constexpr auto CarnivoreConeDepthOffset = 0;
        constexpr auto HerbivoreConeDepthOffset = 50;
        constexpr auto OmnivoreConeDepthOffset = 15;
        constexpr auto HerbConeDepthOffset = 0;

        // Speed
        constexpr auto MaxSpawnSpeed = 50;
        constexpr auto MinSpawnSpeed = 0;
        constexpr auto CarnivoreSpeedOffset = 30;
        constexpr auto HerbivoreSpeedOffset = 50;
        constexpr auto OmnivoreSpeedOffset = 25;
        constexpr auto HerbSpeedOffset = 0;

        // Aggression
        constexpr auto MaxSpawnAggression = 50;
        constexpr auto MinSpawnAggression = 0;
        constexpr auto CarnivoreAggressionOffset = 50;
        constexpr auto HerbivoreAggressionOffset = 10;
        constexpr auto OmnivoreAggressionOffset = 30;
        constexpr auto HerbAggressionOffset = 0;

        // shape
        constexpr auto MinEdges = 3;
        constexpr auto MaxEdges = 10;
        constexpr auto MinRadius = 2;
        constexpr auto MaxRadius = 5;
        const sf::Color SpawnColor = sf::Color::White;
        const sf::Color CarnivoreSpawnColor = sf::Color::Red;
        const sf::Color HerbivoreSpawnColor = sf::Color::Blue;
        const sf::Color OmnivoreSpawnColor = sf::Color::Yellow;
        const sf::Color HerbsSpawnColor = sf::Color::Green;

        struct Attributes
        {
            // list is priority wise
            /*
                0-35 -> LOW
                35-80 -> MEDIUM
                80-100 -> HIGH
            */
            EnergyBand state{EnergyBand::HIGH};
            Resolution energy{0};
            /*
                LOW -> 100
                MEDIUM -> value
                HIGH -> 0
            */
            Resolution aggression{0}, aggressionbackup{0};
            Resolution speed{0}, speedbackup{0};
            Resolution stamina{0}, staminabackup{0};

            bool setLow{false};

            Resolution visionConeAngle{0};
            Resolution visionDepth{0};

            NFResolution32 id;
            sf::Vector2f position;
            SpeciesType type;
            SpeciesSubType subType;
            sf::Text label;

            // future scope
            Resolution socializing{0};

            Resolution getValidValue(Resolution value)
            {
                if (value > 100)
                    value = 100;

                return value;
            }

            void UpdateLifeSpan(Resolution span = -1)
            {
                Resolution factor = 0;
                if (energy <= MinThresholdEnergy)
                {
                    if (!setLow)
                    {
                        setLow = true;
                        aggression = 100;
                        speed = getValidValue(speed + speed * 1.5);
                        stamina = getValidValue(stamina + stamina * 1.5);
                        state = EnergyBand::LOW;
                    }

                    if (setLow)
                    {
                        factor = 0.1;
                    }
                }
                else if (energy < MaxThresholdEnergy && energy > MinThresholdEnergy)
                {
                    state = EnergyBand::MEDIUM;
                    aggression = aggressionbackup;
                    speed = speedbackup;
                    stamina = staminabackup;
                    factor = 0.05;
                    setLow = false;
                }
                else
                {
                    state = EnergyBand::HIGH;
                    aggression = 0;
                    speed = speedbackup;
                    stamina = staminabackup;
                    setLow = false;
                }

                energy = energy + span + span * factor;
            }
        };
    }

    namespace Behaviour
    {
        enum class ReactionType : uint8_t
        {
            INVALID = 254,
            KILL = 0, // This will just kill
            IGNORE = 1,
            RUN = 2,
            FIGHT = 3,
            GROUP = 4,
            CONSUME = 5, // This will kill and transfer the energy
        };
        using ReactionCb = std::function<void(Movement::TargetMovementInfo)>;

        struct OrganismReactionInfo
        {
            ReactionType reaction;
            Manager::EntityId id;
        };

        using MapOfOrganismInfo = std::unordered_map<NFResolution32, OrganismReactionInfo>;
    }
}

#endif