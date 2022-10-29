#ifndef IORGANISMENTITY_HPP
#define IORGANISMENTITY_HPP

#include "IEntity.hpp"
#include "IBehaviourHandler.hpp"
#include "IConfig.hpp"
#include "CUtility.hpp"

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

            std::string ToString()
            {
                std::string stats;

                stats += "#) ";
                stats += "ID: ";
                stats += std::to_string(m_attributes->id);
                stats += "\t";

                stats += "#) ";
                stats += "Type: ";
                stats += pEnum(m_attributes->type);
                stats += "\t";

                stats += "#) ";
                stats += "Sub Type: ";
                stats += pEnum(m_attributes->subType);
                stats += "\n\n";

                stats += "#) ";
                stats += "Position: ";
                stats += std::to_string(getPosition().x);
                stats += ", ";
                stats += std::to_string(getPosition().y);
                stats += "\n\n";

                stats += "#) ";
                stats += "Aggression: ";
                stats += std::to_string(m_attributes->aggression);
                stats += "\n";

                stats += "#) ";
                stats += "Energy: ";
                stats += std::to_string(m_attributes->energy);
                stats += "\n";

                stats += "#) ";
                stats += "Speed: ";
                stats += std::to_string(m_attributes->speed);
                stats += "\n";

                stats += "#) ";
                stats += "Stamina: ";
                stats += std::to_string(m_attributes->stamina);
                stats += "\n";

                stats += "#) ";
                stats += "Vision Depth: ";
                stats += std::to_string(m_attributes->visionDepth);
                stats += "\n";

                stats += "#) ";
                stats += "Vision Cone Angle: ";
                stats += std::to_string(m_attributes->visionConeAngle);
                stats += "\n\n";

                stats += "#) ";
                stats += "Organisms in view:\n\n";

#ifdef DEBUG_MODE
                const auto list = m_behaviour->m_organismsInView;
                for (auto entity : list)
                {
                    stats += std::to_string(entity.first) + " : " + pEnum(entity.second.reaction) + "\n";
                }

                stats += "\n";

                stats += "#) ";
                stats += "Priority Target: ";
                stats += std::to_string(m_behaviour->m_mostPriorityTarget);
                stats += "\n\n";

                stats += "#) ";
                stats += "TargetID: ";
                stats += pEnum(m_targetOperationInfo.targetId);
                stats += "\n";

                stats += "#) ";
                stats += "Operations: ";
                stats += "\n";

                for (auto operation : m_targetOperationInfo.operations)
                {
                    stats += "* ";
                    stats += pEnum(operation);
                    stats += "\n";
                }
                stats += "\n";
#endif

                return stats;
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