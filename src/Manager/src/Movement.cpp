#include "Movement.hpp"
#include "IConfig.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{
    Movement::Movement(std::shared_ptr<EntityMatrix> matrix) : m_matrix(matrix)
    {
    }
    Evolution::Manager::EntityId Movement::RegisterToMove(Evolution::Manager::EntityId orgId, Evolution::Movement::MovementType type)
    {
        MovementInfo info;
        info.type = type;
        info.steps = 0;
        info.hemisphere = Utility::Hemisphere::UPPER;
        info.quadrant = Utility::Quadrant::FIRST;

        m_organismsMovementInfo.insert({orgId, info});
        return ++m_subscriptionId;
    }

    void Movement::UpdateMovement(Evolution::Manager::EntityId id, Evolution::Movement::MovementType type)
    {
        m_organismsMovementInfo[id].type = type;
    }

    void Movement::UnRegisterToMove(Evolution::Manager::EntityId id)
    {
        auto itr = m_organismsMovementInfo.find(id);
        if (itr != m_organismsMovementInfo.end())
        {
            m_organismsMovementInfo.erase(itr);
        }
    }

    void Movement::Move()
    {
        for (auto &org : m_organismsMovementInfo)
        {
            auto movementAttr = m_matrix->GetEntity(org.first)->FetchMovementOperations();

            switch (org.second.type)
            {
            case Evolution::Movement::MovementType::Randomly:
                MoveRandomly(org.first);
                break;
            case Evolution::Movement::MovementType::Purposely:
                MovePurposely(org.first);
                break;
            case Evolution::Movement::MovementType::Chase:
                Chase(org.first);
                break;
            }

            if (m_matrix->GetEntityMatrix().find(movementAttr.targetId) == m_matrix->GetEntityMatrix().end())
            {
                continue;
            }

            for (auto operation : movementAttr.operations)
            {
                UpdateMovementOperation(org.first, movementAttr.targetId, operation);
            }
        }

        for (auto it : m_unregisteredList)
        {
            UnRegisterToMove(it.second);
            m_matrix->ResetPriority(it.first, it.second);
            m_matrix->RemoveTargetEncounteredInfo(it.first, it.second);
            m_matrix->RemoveEntity(it.second);
        }
        m_unregisteredList.clear();
    }

    void Movement::ResetOnBoundryEncounter(sf::Vector2f &pos)
    {
        if (pos.x >= Utility::Width)
        {
            pos.x = 0;
        }
        else if (pos.x <= 0)
        {
            pos.x = Utility::Width;
        }

        if (pos.y >= Utility::Height)
        {
            pos.y = 0;
        }
        else if (pos.y <= 0)
        {
            pos.y = Utility::Height;
        }
    }

    Resolution Movement::GetRandomDirectionForEntity(Evolution::Manager::EntityId id)
    {
        auto &info = m_organismsMovementInfo[id];

        info.steps = CUtility::GetRandomValueInRange(Evolution::Movement::MinSteps, Evolution::Movement::MaxSteps);
        auto hemisphereProbability = CUtility::GetProbability();

        if (hemisphereProbability >= Utility::ProbabilityFor)
        {
            info.hemisphere = static_cast<Utility::Hemisphere>(static_cast<int8_t>(info.hemisphere) * -1);
        }

        auto quadrantProbability = CUtility::GetProbability();

        if (quadrantProbability >= Utility::ProbabilityFor)
        {
            auto quadCnt = CUtility::GetRandomValueInRange(0, Utility::TotalQuadrant / 2);
            if (info.hemisphere == Utility::Hemisphere::LOWER)
            {
                quadCnt += Utility::TotalQuadrant / 2;
            }
            info.quadrant = static_cast<Utility::Quadrant>(quadCnt);
        }

        auto angle = CUtility::GetRandomValueInRange(0, Utility::TotalAngle / Utility::TotalQuadrant);
        angle += ((Utility::TotalAngle / Utility::TotalQuadrant) * info.quadrant);
        return angle;
    }

    sf::Vector2f Movement::GetNewPosition(Resolution angle, Resolution speed, sf::Vector2f currentPosition)
    {
        sf::Vector2f newPos;
        auto ratio = CUtility::GetMovementRatio(angle);
        auto yToMove = ratio.y * speed / 100;
        auto xToMove = ratio.x * speed / 100;
        newPos = sf::Vector2f(currentPosition.x + xToMove, currentPosition.y + yToMove);
        ResetOnBoundryEncounter(newPos);
        return newPos;
    }

    void Movement::MoveRandomly(Evolution::Manager::EntityId id)
    {
        auto &info = m_organismsMovementInfo[id];
        auto entity = m_matrix->GetEntity(id);
        auto attributes = entity->GetAttributes();

        if (info.steps <= 0)
        {
            entity->setRotation(GetRandomDirectionForEntity(id));
            if (entity->getFillColor() == sf::Color::White)
            {
                entity->setFillColor(sf::Color::Green);
            }
        }

        entity->setPosition(GetNewPosition(entity->getRotation(), attributes->speed, entity->getPosition()));
        info.steps -= Utility::StepReductionFactor;
    }

    void Movement::MovePurposely(Evolution::Manager::EntityId)
    {
    }
    void Movement::MoveToPoint(sf::Vector2f)
    {
    }

    sf::Vector2f Movement::Interpolate(
        const sf::Vector2f &pointA,
        const sf::Vector2f &pointB, Resolution speed)
    {
        auto diff = pointB - pointA;
        if (diff.x == 0)
        {
            return {pointA.x, (pointA.y + 1)};
        }
        else if (diff.y == 0)
        {
            return {(pointA.x + 1), pointA.y};
        }
        else
        {
            return {(pointA.x + 1), (pointA.y + diff.y / diff.x)};
        }
        // auto angle = std::atan(diff.y / diff.x);
        // std::cout << "Angle: " << angle << std::endl;

        // auto ratio = CUtility::GetMovementRatio(CUtility::RadiansToDegree(angle));
        // auto yToMove = ratio.y * speed / 100;
        // auto xToMove = ratio.x * speed / 100;
        // return pointA + (pointB - pointA) * speed * m_factor;
    }

    void Movement::Chase(Evolution::Manager::EntityId orgid)
    {
        auto targetid = m_organismsMovementInfo[orgid].target;
        auto &info = m_organismsMovementInfo[orgid];

        auto org = m_matrix->GetEntity(orgid);

        org->setFillColor(sf::Color::Magenta);
        auto attributes = org->GetAttributes();
        auto target = m_matrix->GetEntity(targetid);

        if (CUtility::GetDistanceBetweenPoints(org->getPosition(), target->getPosition()) > attributes->visionDepth / 8)
        {
            // org->setPosition(GetNewPosition(target->getRotation(), attributes->speed, org->getPosition()));
            org->setPosition(Interpolate(org->getPosition(), target->getPosition(), attributes->speed));
        }

        else
        {
            std::cout << orgid << " Killed " << targetid << std::endl;
            org->setFillColor(sf::Color::Red);
            m_unregisteredList.push_back({orgid, targetid});
            info.type = Evolution::Movement::MovementType::Randomly;
        }
        info.steps -= Utility::StepReductionFactor;
        if (info.steps <= 0)
        {
            org->setFillColor(sf::Color::Red);
            info.type = Evolution::Movement::MovementType::Randomly;
        }
    }

    void Movement::UpdateMovementOperation(const Evolution::Manager::EntityId &orgid, const Evolution::Manager::EntityId &targetid, Evolution::Movement::MovementOperation operation)
    {
#ifdef LOG
        // std::cout << "\t" << pEnum(operation) << std::endl;
#endif
        auto org = m_matrix->GetEntity(orgid);
        switch (operation)
        {
        case Evolution::Movement::MovementOperation::IncrementSpeed:
            org->GetAttributes()->speed += Utility::SpeedEnhancementFactor;
            break;
        case Evolution::Movement::MovementOperation::DecrementSpeed:
            if (org->GetAttributes()->speed > Utility::SpeedReductionFactor)
            {
                org->GetAttributes()->speed -= Utility::SpeedReductionFactor;
            }
            break;
        case Evolution::Movement::MovementOperation::RotateBy180:
            org->setRotation(org->getRotation() + Utility::TotalAngle / Utility::TotalHemisphere);
            break;
        case Evolution::Movement::MovementOperation::RotateBy90:
            org->setRotation(org->getRotation() + Utility::TotalAngle / Utility::TotalQuadrant);
            break;
        case Evolution::Movement::MovementOperation::RotateByRandom:
            org->setRotation(org->getRotation() + CUtility::GetRandomValueInRange(0, Utility::TotalAngle));
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToKill:
            m_organismsMovementInfo[orgid].target = targetid;
            m_organismsMovementInfo[orgid].type = Evolution::Movement::MovementType::Chase;
            m_organismsMovementInfo[orgid].steps += 100;

            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToGroup:
            // org->setFillColor(sf::Color::Green);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToIgnore:
            // org->setFillColor(sf::Color::Cyan);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToFight:
            org->setFillColor(sf::Color::Yellow);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToRun:
            org->setFillColor(sf::Color::White);
            m_organismsMovementInfo[orgid].steps += 100;
            break;
        }
    }
}