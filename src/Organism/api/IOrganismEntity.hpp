#ifndef IORGANISMENTITY_HPP
#define IORGANISMENTITY_HPP

#include "IEntity.hpp"
#include "IConfig.hpp"

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

        struct Attributes
        {
            Resolution m_speed{0};
            Resolution m_vision{0};
            Resolution m_stamina{0};
            Resolution m_energy{0};
        };

        class IOrganismEntity : public IEntity
        {
        public:
            Attributes GetAttributes() const;

        protected:
            void OnEncounter();

            Attributes m_attributes;
            OrganismType m_foodType;
        };
    }
}

#endif