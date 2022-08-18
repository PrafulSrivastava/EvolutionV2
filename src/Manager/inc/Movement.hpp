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
        void UpdateMovementOperation(Evolution::Manager::EntityId, Evolution::Movement::MovementOperation) override;

    private:
        void MoveRandomly(Evolution::Manager::EntityId);
        void MovePurposely(Evolution::Manager::EntityId);
        void ResetOnBoundryEncounter(sf::Vector2f &pos);
        NFResolution16 m_subscriptionId{-1};
        std::unordered_map<Evolution::Manager::EntityId, MovementInfo> m_organismsMovementInfo;
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
    };
}

#endif