#ifndef IORGANISMENTITY_HPP
#define IORGANISMENTITY_HPP

#include "IEntity.hpp"
#include "IBehaviourHandler.hpp"
#include "IConfig.hpp"
#include <memory>

namespace Evolution
{
    namespace Organism
    {

        class IOrganismEntity : public CEntityWrapper<sf::CircleShape>
        {
        public:
            std::shared_ptr<Attributes> GetAttributes() const
            {
                return m_attributes;
            }

            void RemoveIfNotInVision(const Manager::EntityId &id)
            {
                m_behaviour->RemoveIfNotInVision(id);
            }

            void OnCollision(std::shared_ptr<Attributes> targetAttributes)
            {
                m_behaviour->OnCollision(targetAttributes);
            }

            void OnEncounter(std::shared_ptr<Attributes> orgAttributes, std::shared_ptr<Attributes> targetAttributes)
            {
                m_behaviour->OnEncounter(orgAttributes, targetAttributes);
            }

            void SetMostPriorityTarget(Manager::EntityId index)
            {
                m_behaviour->SetMostPriorityTarget(index);
            }

            void OnReaction(Movement::Operations operations)
            {
                m_operations.operations.clear();
                m_operations.targetId = operations.targetId;
                m_operations.operations = std::move(operations.operations);
                m_reactionChanged = true;
            }

            NFResolution32 GetEntityId()
            {
                return m_attributes->id;
            }

            void SetCurrentPos(sf::Vector2f pos)
            {
                m_attributes->position = pos;
            }

            Movement::Operations FetchMovementOperations()
            {
                if (m_reactionChanged)
                {
                    m_reactionChanged = false;
                    return m_operations;
                }
                return {};
            }

        protected:
            std::mutex m_mtx;
            std::shared_ptr<Evolution::Behaviour::IBehaviourHandler>
                m_behaviour{nullptr};
            std::shared_ptr<Attributes> m_attributes{nullptr};
            OrganismType m_type{OrganismType::INVALID};
            Behaviour::ReactionType m_reaction{Behaviour::ReactionType::INVALID};
            Movement::Operations m_operations{{Movement::MovementOperation::INVALID}, Manager::InvalidEntityId};
            bool m_reactionChanged{false};
        };
    }
}

#endif