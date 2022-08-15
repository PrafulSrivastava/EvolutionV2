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
            sf::Vector2f position;
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

                // Need to replace with priority queue
                std::lock_guard<std::mutex> lck(m_mtx);
                m_organismsInView[targetAttributes->id] = {reaction, targetAttributes->position};
                m_hasNewPoi = true;
            }

            void RegisterForReaction(ReactionCb callback)
            {
                m_reactionCb = callback;
            }

            virtual void RunMainLoop(sf::Vector2f orgPos)
            {
            }

        protected:
            MapOfOrganismInfo m_organismsInView;
            std::mutex m_mtx;
            bool m_hasNewPoi{false};
            ReactionCb m_reactionCb{nullptr};
            Organism::OrganismType m_type{Organism::OrganismType::INVALID};
        };
    }
}

#endif