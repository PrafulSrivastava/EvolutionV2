#ifndef REACTION_HPP
#define REACTION_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif
#include "IConfig.hpp"

#include <memory>

namespace Evolution
{
    namespace Behaviour
    {
        struct ReactionInfo
        {
            std::shared_ptr<Evolution::Organism::Attributes> org, target;
            Manager::Priority priority;
            ReactionType reaction;
        };

        class Reaction
        {
        public:
            static Reaction &GetInstance();
            ReactionType FetchReaction(ReactionInfo &);
            std::vector<Movement::MovementOperation> React(Evolution::Organism::OrganismType, Behaviour::ReactionType);

        private:
            Reaction() = default;
            ~Reaction() = default;

            ReactionType FetchCarnivoreReaction(ReactionInfo &);
            ReactionType FetchHerbivoreReaction(ReactionInfo &);
            ReactionType FetchOmnivoreReaction(ReactionInfo &);
            std::vector<Movement::MovementOperation> ReactCarnivore(Behaviour::ReactionType);
            std::vector<Movement::MovementOperation> ReactHerbivore(Behaviour::ReactionType);
            std::vector<Movement::MovementOperation> ReactOmnivore(Behaviour::ReactionType);
        };
    }
}

#endif