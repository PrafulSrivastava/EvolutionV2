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
            std::shared_ptr<Organism::Attributes> GetAttributes() const override
            {
                return m_attributes;
            }

            void RemoveIfNotInVision(const Manager::EntityId &id) override
            {
                m_behaviour->RemoveIfNotInVision(id);
            }

            void OnCollision(std::shared_ptr<Attributes> targetAttributes) override
            {
                m_behaviour->OnCollision(targetAttributes);
            }

            void OnEncounter(std::shared_ptr<Attributes> orgAttributes, std::shared_ptr<Attributes> targetAttributes) override
            {
                m_behaviour->OnEncounter(orgAttributes, targetAttributes);
            }

            void SetMostPriorityTarget(Manager::EntityId index) override
            {
                m_behaviour->SetMostPriorityTarget(index);
            }

            void OnReaction(Movement::TargetMovementInfo targetOperationInfo) override
            {
                m_targetOperationInfo.operations.clear();
                m_targetOperationInfo.targetId = targetOperationInfo.targetId;
                m_targetOperationInfo.operations = std::move(targetOperationInfo.operations);
                m_reactionChanged = true;
            }

            NFResolution32 GetEntityId() override
            {
                return m_attributes->id;
            }

            void SetCurrentPos(sf::Vector2f pos) override
            {
                m_attributes->position = pos;
            }

            Movement::TargetMovementInfo FetchMovementOperations() override
            {
                if (m_reactionChanged)
                {
                    m_reactionChanged = false;
                    return m_targetOperationInfo;
                }
                return {};
            }

        protected:
            std::mutex m_mtx;
            std::shared_ptr<Evolution::Behaviour::IBehaviourHandler>
                m_behaviour{nullptr};
            std::shared_ptr<Attributes> m_attributes{nullptr};
            SpeciesType m_type{SpeciesType::INVALID};
            Behaviour::ReactionType m_reaction{Behaviour::ReactionType::INVALID};
            Movement::TargetMovementInfo m_targetOperationInfo{{Movement::MovementOperation::INVALID}, Manager::InvalidEntityId};
            bool m_reactionChanged{false};
        };
    }
}

#endif