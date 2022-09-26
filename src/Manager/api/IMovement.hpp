#ifndef IMOVEMENT_HPP
#define IMOVEMENT_HPP

#include "IOrganismEntity.hpp"
#include "IConfig.hpp"
#include <vector>
#include <memory>

namespace Evolution::Manager
{

    struct MovementInfo
    {
        Evolution::Movement::MovementType type;
        NFResolution16 steps;
        Utility::Hemisphere hemisphere;
        Utility::Quadrant quadrant;
        Manager::EntityId target{Manager::InvalidEntityId};
    };

    class IMovement
    {
    public:
        virtual Evolution::Manager::EntityId RegisterToMove(Evolution::Manager::EntityId, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovement(Evolution::Manager::EntityId, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovementOperation(const Evolution::Manager::EntityId &, const Evolution::Manager::EntityId &, Evolution::Movement::MovementOperation) = 0;
        virtual void UnRegisterToMove(Evolution::Manager::EntityId) = 0;
        virtual void Move() = 0;
        virtual void MoveToPoint(sf::Vector2f) = 0;
    };
}

#endif