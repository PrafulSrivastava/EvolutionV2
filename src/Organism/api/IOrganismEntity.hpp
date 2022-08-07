#ifndef IORGANISMENTITY_HPP
#define IORGANISMENTITY_HPP

#include "IEntity.hpp"
#include "IConfig.hpp"
#include <memory>

namespace Evolution
{
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

            OrganismType type;
            MessageType message;
        };

        class IOrganismEntity : public CEntityWrapper<sf::CircleShape>
        {
        public:
            Attributes GetAttributes() const
            {
                return m_attributes;
            }

        protected:
            void OnEncounter();

            Attributes m_attributes;
            OrganismType m_foodType;
        };
    }
}

#endif