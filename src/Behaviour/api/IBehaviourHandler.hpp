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

            void RemoveIfNotInVision(const Manager::EntityId &id)
            {
                auto itorg = m_organismsInView.find(id);
                if (itorg != m_organismsInView.end())
                {
                    // std::cout << "Removing : " << id << std::endl;

                    if (m_mostPriorityTarget == id)
                        m_hasNewPoi = false;

                    m_organismsInView.erase(itorg);
                }
            }

            void OnEncounter(std::shared_ptr<Organism::Attributes> orgAttributes, std::shared_ptr<Organism::Attributes> targetAttributes)
            {
                // currentId = targetAttributes->id;

                if (m_organismsInView.find(targetAttributes->id) == m_organismsInView.end())
                {
                    ReactionInfo info = {orgAttributes,
                                         targetAttributes,
                                         0,
                                         FetchTargetReaction(targetAttributes->id)};

                    auto reaction = Reaction::GetInstance().FetchReaction(info);
                    // std::cout << "Adding target : " << targetAttributes->id << " to " << orgAttributes->id << std::endl;
                    m_organismsInView[targetAttributes->id] = {reaction, targetAttributes->id};
                    // std::cout << "m_hasNewPoi : " << m_hasNewPoi << " for " << orgAttributes->id << std::endl;
                    m_hasNewPoi = true;
                }
            }

            void RegisterForReaction(ReactionCb callback)
            {
                m_reactionCb = callback;
            }

            ReactionType FetchTargetReaction(Manager::EntityId target)
            {
                if (m_organismsInView.find(target) != m_organismsInView.end())
                {
                    return m_organismsInView[target].reaction;
                }
                else
                {
                    return ReactionType::INVALID;
                }
            }

            virtual void RunMainLoop(sf::Vector2f orgPos)
            {
            }

            void SetMostPriorityTarget(Manager::EntityId index)
            {
                // if (m_mostPriorityTarget != index)
                // {
                //     // std::cout << "Setting Most Prio target to " << index << " for " << m_orgId << std::endl;
                m_mostPriorityTarget = index;
                // std::cout << "m_mostPriorityTarget " << m_mostPriorityTarget << std::endl;
                // }
            }

            void SetOrgId(Manager::EntityId id)
            {
                m_orgId = id;
            }

        protected:
            Manager::EntityId m_orgId{-1};
            MapOfOrganismInfo m_organismsInView;
            Manager::EntityId m_mostPriorityTarget;
            bool m_hasNewPoi{false};
            ReactionCb m_reactionCb{nullptr};
            Organism::OrganismType m_type{Organism::OrganismType::INVALID};
        };
    }
}

#endif