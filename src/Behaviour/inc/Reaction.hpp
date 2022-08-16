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

        class Reaction
        {
        public:
            static Reaction &GetInstance();
            ReactionType FetchReaction(std::shared_ptr<Evolution::Organism::Attributes> orgAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes);
            std::vector<Movement::MovementOperation> React(Evolution::Organism::OrganismType, Behaviour::ReactionType);

        private:
            Reaction() = default;
            ~Reaction() = default;

            ReactionType FetchCarnivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> orgAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes);
            ReactionType FetchHerbivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> orgAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes);
            ReactionType FetchOmnivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> orgAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes);
            std::vector<Movement::MovementOperation> ReactCarnivore(Behaviour::ReactionType);
            std::vector<Movement::MovementOperation> ReactHerbivore(Behaviour::ReactionType);
            std::vector<Movement::MovementOperation> ReactOmnivore(Behaviour::ReactionType);
        };
    }
}

#endif