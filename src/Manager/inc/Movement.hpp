#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "IMovement.hpp"
#include <vector>
#include <memory>

namespace Evolution::Manager
{
    class Movement : public IMovement
    {
    public:
        Movement() = default;
        ~Movement() = default;
        Movement(const Movement &) = default;
        Movement &operator=(const Movement &) = default;
        Movement(Movement &&) = default;
        Movement &operator=(Movement &&) = default;

        int16_t RegisterToMove(std::shared_ptr<Evolution::Organism::IOrganismEntity>, Evolution::Movement::MovementType) override;
        void UpdateMovement(int16_t, Evolution::Movement::MovementType) override;
        void UnRegisterToMove(int16_t) override;
        void Move() override;
        void MoveToPoint(sf::Vector2f) override;
        void UpdateMovementOperation(int16_t, Evolution::Movement::MovementOperation) override;

    private:
        void MoveRandomly(MovementInfo &);
        void MovePurposely(MovementInfo &);
        void ResetOnBoundryEncounter(sf::Vector2f &pos);
        int16_t m_subscriptionId{-1};
        std::vector<MovementInfo> m_organismsMovementInfo;
    };
}

#endif