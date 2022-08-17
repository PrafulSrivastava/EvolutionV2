#ifndef IBEHAVIOURHANDLER_HPP
#define IBEHAVIOURHANDLER_HPP

#include "IConfig.hpp"
#include "Reaction.hpp"
#include <unordered_map>
#include <mutex>
namespace Evolution
{
    namespace Behaviour
    {

        struct OrganismReactionInfo
        {
            ReactionType reaction;
            Manager::EntityId id;
        };

        using MapOfOrganismInfo = std::unordered_map<NFResolution32, OrganismReactionInfo>;
        class IBehaviourHandler
        {
        public:
            void OnCollision(std::shared_ptr<Organism::Attributes> orgAttributes)
            {
                // TO DO
            }

            void OnEncounter(std::shared_ptr<Organism::Attributes> orgAttributes, std::shared_ptr<Organism::Attributes> targetAttributes)
            {
                auto reaction = Reaction::GetInstance().FetchReaction(orgAttributes, targetAttributes);
                m_organismsInView[targetAttributes->id] = {reaction, targetAttributes->id};
                m_hasNewPoi = true;
            }

            void RegisterForReaction(ReactionCb callback)
            {
                m_reactionCb = callback;
            }

            virtual void RunMainLoop(sf::Vector2f orgPos)
            {
            }

            virtual void SetMostPriorityTarget(Manager::EntityId index)
            {
                m_mostPriorityTarget = index;
            }

        protected:
            MapOfOrganismInfo m_organismsInView;
            Manager::EntityId m_mostPriorityTarget;
            bool m_hasNewPoi{false};
            ReactionCb m_reactionCb{nullptr};
            Organism::OrganismType m_type{Organism::OrganismType::INVALID};
        };
    }
}

#endif