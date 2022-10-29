#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "IMovement.hpp"
#include <unordered_map>
#include <memory>
#include "EntityMatrix.hpp"
#include "CUtility.hpp"

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

        std::string ToString(const Evolution::Manager::EntityId &id) override
        {
            if (m_organismsMovementInfo.find(id) == m_organismsMovementInfo.end())
            {
                return {};
            }
            const Evolution::Movement::MovementInfo &info = m_organismsMovementInfo[id];
            std::string infoStr{};

            infoStr += "#) ";
            infoStr += "Hemisphere: ";
            infoStr += pEnum(info.hemisphere);
            infoStr += "\t";

            infoStr += "#) ";
            infoStr += "Quadrant: ";
            infoStr += pEnum(info.quadrant);
            infoStr += "\t";

            infoStr += "#) ";
            infoStr += "Steps: ";
            infoStr += std::to_string(info.steps);
            infoStr += "\n\n";

            infoStr += "#) ";
            infoStr += "TargetID: ";
            infoStr += std::to_string(info.target);
            infoStr += "\t";

            infoStr += "#) ";
            infoStr += "MovementType: ";
            infoStr += pEnum(info.type);
            infoStr += "\n";

            return infoStr;
        }

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
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
    };
}

#endif