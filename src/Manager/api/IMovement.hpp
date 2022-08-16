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
        NFResolution32 organismId;
    };

    class IMovement
    {
    public:
        virtual NFResolution16 RegisterToMove(NFResolution32, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovement(NFResolution16, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovementOperation(NFResolution16, Evolution::Movement::MovementOperation) = 0;
        virtual void UnRegisterToMove(NFResolution16) = 0;
        virtual void Move() = 0;
        virtual void MoveToPoint(sf::Vector2f) = 0;
    };
}

#endif