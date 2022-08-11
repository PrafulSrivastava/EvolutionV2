#ifndef IBEHAVIOURHANDLER_HPP
#define IBEHAVIOURHANDLER_HPP

#include "IConfig.hpp"
#include "Reaction.hpp"

namespace Evolution
{
    namespace Behaviour
    {

        class IBehaviourHandler
        {
        public:
            void OnCollision(Organism::Attributes orgAttributes)
            {
                // TO DO
            }

            void OnEncounter(Organism::Attributes orgAttributes, Organism::Attributes targetAttributes)
            {
                auto reaction = Evolution::Behaviour::Reaction::GetInstance().React(orgAttributes, targetAttributes);

                // Need to replace with priority queue
                m_hasNewPoi = true;
            }

        protected:
            bool m_hasNewPoi{false}, m_targetReached{false};
            ReactionType m_reaction;
        };
    }
}

#endif