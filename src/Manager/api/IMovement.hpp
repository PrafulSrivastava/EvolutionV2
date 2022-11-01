#ifndef IMOVEMENT_HPP
#define IMOVEMENT_HPP

#include "IOrganismEntity.hpp"
#include "IConfig.hpp"
#include <vector>
#include <memory>

namespace Evolution::Manager
{
    class IMovement
    {
    public:
        virtual Evolution::Manager::EntityId RegisterToMove(Evolution::Manager::EntityId, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovement(Evolution::Manager::EntityId, Evolution::Movement::MovementType) = 0;
        virtual void UpdateMovementOperation(const Evolution::Manager::EntityId &, const Evolution::Manager::EntityId &, Evolution::Movement::MovementOperation) = 0;
        virtual void UnRegisterToMove(Evolution::Manager::EntityId) = 0;
        virtual void Move() = 0;
        virtual void MoveToPoint(sf::Vector2f) = 0;
        virtual std::string ToString(const Evolution::Manager::EntityId &id) = 0;

    protected:
        std::unordered_map<Evolution::Manager::EntityId, Evolution::Movement::MovementInfo> m_organismsMovementInfo;
        std::vector<std::pair<Evolution::Manager::EntityId, Evolution::Manager::EntityId>> m_unregisteredList;
    };
}

#endif