#ifndef REACTION_HPP
#define REACTION_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif
#include "IConfig.hpp"

namespace Evolution
{
    namespace Behaviour
    {

        class Reaction
        {
        public:
            static Reaction &GetInstance();
            ReactionType React(Evolution::Organism::Attributes orgAttributes, Evolution::Organism::Attributes targetAttributes);

        private:
            Reaction() = default;
            ~Reaction() = default;

            ReactionType Carnivore(Evolution::Organism::Attributes orgAttributes, Evolution::Organism::Attributes targetAttributes);

            ReactionType Herbivore(Evolution::Organism::Attributes orgAttributes, Evolution::Organism::Attributes targetAttributes);
        };
    }
}

#endif