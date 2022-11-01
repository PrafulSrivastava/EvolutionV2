#ifndef IBEHAVIOURHANDLER_HPP
#define IBEHAVIOURHANDLER_HPP

#include "IConfig.hpp"
#include "Reaction.hpp"
#include <unordered_map>
#include <mutex>

#ifdef DEBUG_MODE
namespace Evolution::Organism
{
    class IOrganismEntity;
}
#endif
namespace Evolution
{
    namespace Behaviour
    {
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
                    if (m_mostPriorityTarget == id)
                        m_hasNewPoi = false;

                    m_organismsInView.erase(itorg);
                }
            }

            void OnEncounter(std::shared_ptr<Organism::Attributes> orgAttributes, std::shared_ptr<Organism::Attributes> targetAttributes)
            {
                if (m_organismsInView.find(targetAttributes->id) == m_organismsInView.end())
                {
                    ReactionInfo info = {orgAttributes,
                                         targetAttributes,
                                         0,
                                         FetchTargetReaction(targetAttributes->id)};

                    auto reaction = Reaction::GetInstance().FetchReaction(info);
                    m_organismsInView[targetAttributes->id] = {reaction, targetAttributes->id};
                    m_hasNewPoi = true;
                }
            }

            void RegisterForReaction(ReactionCb callback)
            {
                m_reactionCb = callback;
            }

            // This will Fetch the reaction of the target which encountered. Based on the target reaction the organism reaction can change. e.g. A Strong Herbivore(elephant) won't interfere or fight until the other guy tries to attack. In this scenario, the herbivore reaction can change.
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
                m_mostPriorityTarget = index;
                Log(Log::DEBUG, "MostPriorityTargetId", m_mostPriorityTarget);
            }

            void SetOrgId(Manager::EntityId id)
            {
                m_orgId = id;
            }

#ifdef DEBUG_MODE
            friend Evolution::Organism::IOrganismEntity;
#endif

        protected:
            Manager::EntityId m_orgId{-1};
            MapOfOrganismInfo m_organismsInView;
            Manager::EntityId m_mostPriorityTarget;
            bool m_hasNewPoi{false};
            ReactionCb m_reactionCb{nullptr};
            Organism::SpeciesType m_type{Organism::SpeciesType::INVALID};
        };
    }
}

#endif