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

            void OnCollision(std::shared_ptr<Attributes> targetAttributes)
            {
                m_behaviour->OnCollision(targetAttributes);
            }

            void OnEncounter(std::shared_ptr<Attributes> orgAttributes, std::shared_ptr<Attributes> targetAttributes)
            {
                m_behaviour->OnEncounter(orgAttributes, targetAttributes);
            }

            void OnReaction(Movement::Operations operations)
            {
                std::lock_guard<std::mutex> lck(m_mtx);

                m_operations.clear();
                m_operations = std::move(operations);
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
                std::lock_guard<std::mutex> lck(m_mtx);

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
            Movement::Operations m_operations{Movement::MovementOperation::INVALID};
            bool m_reactionChanged{false};
        };
    }
}

#endif