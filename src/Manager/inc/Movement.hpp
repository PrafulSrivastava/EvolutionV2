#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "IMovement.hpp"
#include <vector>
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

        NFResolution16 RegisterToMove(NFResolution32, Evolution::Movement::MovementType) override;
        void UpdateMovement(NFResolution16, Evolution::Movement::MovementType) override;
        void UnRegisterToMove(NFResolution16) override;
        void Move() override;
        void MoveToPoint(sf::Vector2f) override;
        void UpdateMovementOperation(NFResolution16, Evolution::Movement::MovementOperation) override;

    private:
        void MoveRandomly(MovementInfo &);
        void MovePurposely(MovementInfo &);
        void ResetOnBoundryEncounter(sf::Vector2f &pos);
        NFResolution16 m_subscriptionId{-1};
        std::vector<MovementInfo> m_organismsMovementInfo;
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
    };
}

#endif