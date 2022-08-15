#ifndef ICONFIG_HPP
#define ICONFIG_HPP

#include <bitset>
#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Evolution
{
    using Resolution = float;
    using NFResolution = int32_t;
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
    namespace Utility
    {
        constexpr auto Height = 600;
        constexpr auto FrameLimit = 120;
        constexpr auto Width = 800;
        constexpr auto WindowName = "EVOLUTION";
        constexpr auto Pi = 3.147;
        constexpr auto TotalAngle = 360;
    }

    namespace Movement
    {
        constexpr auto MinSteps = 60;
        constexpr auto MaxSteps = 100;
        enum class MovementType : uint8_t
        {
            Randomly = 0,
            Purposely = 1
        };

        enum class MovementOperation : uint8_t
        {
            INVALID = 254,
            IncrementSpeed = 0,
            DecrementSpeed,
            RotateBy180,
            RotateBy90,
            RotateByRandom,
            ChangeMotionToKill,
            ChangeMotionToGroup,
            ChangeMotionToIgnore,
            ChangeMotionToFight,
            ChangeMotionToRun,
        };

        using Operations = std::vector<Movement::MovementOperation>;
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

        enum class MessageType : uint8_t
        {
            INVALID = 254,
            GROUP = 1
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
            NFResolution id;
            sf::Vector2f position;

            OrganismType type;
            MessageType message;
        };
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
        };

        using ReactionCb = std::function<void(Movement::Operations)>;
    }

}

#endif