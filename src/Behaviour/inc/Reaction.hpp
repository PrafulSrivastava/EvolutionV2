#ifndef REACTION_HPP
#define REACTION_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include "IOrganismEntity.hpp"

namespace Evolution
{
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

        class Reaction
        {
        public:
            static Reaction &GetInstance();
            ReactionType React(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism, std::shared_ptr<Evolution::Organism::IOrganismEntity> target);

        private:
            Reaction() = default;
            ~Reaction() = default;

            ReactionType Carnivore(Evolution::Organism::Attributes organism, Evolution::Organism::Attributes target);

            ReactionType Herbivore(Evolution::Organism::Attributes organism, Evolution::Organism::Attributes target);
        };
    }
}

#endif