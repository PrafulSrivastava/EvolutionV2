#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "IMovement.hpp"
#include <unordered_map>
#include <memory>
#include "EntityMatrix.hpp"

namespace Evolution::Manager
{
    class Movement : public IMovement
    {
    public:
        Movement(std::shared_ptr<EntityMatrix>);
        ~Movement() = default;
        Movement(const Movement &) = default;
        Movement &operator=(const Movement &) = default;
        Movement(Movement &&) = default;
        Movement &operator=(Movement &&) = default;

        Evolution::Manager::EntityId RegisterToMove(Evolution::Manager::EntityId, Evolution::Movement::MovementType) override;
        void UpdateMovement(Evolution::Manager::EntityId, Evolution::Movement::MovementType) override;
        void UnRegisterToMove(Evolution::Manager::EntityId) override;
        void Move() override;
        void MoveToPoint(sf::Vector2f) override;
        void UpdateMovementOperation(const Evolution::Manager::EntityId &, const Evolution::Manager::EntityId &, Evolution::Movement::MovementOperation) override;

    private:
        float m_factor = 0.0001;
        void MoveRandomly(Evolution::Manager::EntityId);
        Resolution GetRandomDirectionForEntity(Evolution::Manager::EntityId);
        sf::Vector2f GetNewPosition(Resolution, Resolution, sf::Vector2f);
        void MovePurposely(Evolution::Manager::EntityId);
        void Chase(Evolution::Manager::EntityId);
        void ResetOnBoundryEncounter(sf::Vector2f &);
        sf::Vector2f Interpolate(
            const sf::Vector2f &,
            const sf::Vector2f &,
            Resolution);

        NFResolution16 m_subscriptionId{-1};
        std::unordered_map<Evolution::Manager::EntityId, MovementInfo> m_organismsMovementInfo;
        std::vector<std::pair<Evolution::Manager::EntityId, Evolution::Manager::EntityId>> m_unregisteredList;
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
    };
}

#endif