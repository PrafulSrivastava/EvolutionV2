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
        int steps;
        int hemisphere;
        int quadrant;
        std::shared_ptr<Evolution::Organism::IOrganismEntity> organism;
    };

    class IMovement
    {
    public:
        virtual int16_t RegisterToMove(std::shared_ptr<Evolution::Organism::IOrganismEntity>, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovement(int16_t, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovementOperation(int16_t, Evolution::Movement::MovementOperation) = 0;
        virtual void UnRegisterToMove(int16_t) = 0;
        virtual void Move() = 0;
        virtual void MoveToPoint(sf::Vector2f) = 0;
    };
}

#endif