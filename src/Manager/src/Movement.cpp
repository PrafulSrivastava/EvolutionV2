#include "Movement.hpp"
#include "IConfig.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{
    Movement::Movement(std::shared_ptr<EntityMatrix> matrix) : m_matrix(matrix)
    {
    }
    NFResolution16 Movement::RegisterToMove(NFResolution32 orgId, Evolution::Movement::MovementType type)
    {
        MovementInfo info;
        info.organismId = orgId;
        info.type = type;
        info.steps = 0;
        info.hemisphere = Utility::Hemisphere::UPPER;
        info.quadrant = Utility::Quadrant::FIRST;

        m_organismsMovementInfo.push_back(info);
        return ++m_subscriptionId;
    }

    void Movement::UpdateMovement(NFResolution16 id, Evolution::Movement::MovementType type)
    {
        m_organismsMovementInfo[id].type = type;
    }

    void Movement::UnRegisterToMove(NFResolution16 id)
    {
        m_organismsMovementInfo.erase(m_organismsMovementInfo.begin() + id);
    }

    void Movement::Move()
    {
        for (NFResolution32 i = 0; i < m_organismsMovementInfo.size(); i++)
        {
            switch (m_organismsMovementInfo[i].type)
            {
            case Evolution::Movement::MovementType::Randomly:
                MoveRandomly(m_organismsMovementInfo[i]);
                break;
            case Evolution::Movement::MovementType::Purposely:
                MovePurposely(m_organismsMovementInfo[i]);
                break;
            }

            for (auto operation : m_matrix->GetEntity(m_organismsMovementInfo[i].organismId)->FetchMovementOperations())
            {
                UpdateMovementOperation(i, operation);
            }
        }
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

    void Movement::MoveRandomly(MovementInfo &info)
    {

        auto attributes = m_matrix->GetEntity(info.organismId)->GetAttributes();
        if (info.steps <= 0)
        {
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

            auto angle = CUtility::GetRandomValueInRange(0, Utility::TotalAngle / Utility::TotalQuadrant) + (Utility::TotalAngle * info.quadrant);
            m_matrix->GetEntity(info.organismId)->setRotation(angle);
        }

        auto ratio = CUtility::GetMovementRatio(m_matrix->GetEntity(info.organismId)->getRotation());
        auto yToMove = ratio.y * attributes->speed / 100;
        auto xToMove = ratio.x * attributes->speed / 100;
        auto newPos = sf::Vector2f(m_matrix->GetEntity(info.organismId)->getPosition().x + xToMove, m_matrix->GetEntity(info.organismId)->getPosition().y + yToMove);
        ResetOnBoundryEncounter(newPos);

        m_matrix->GetEntity(info.organismId)->setPosition(newPos);
        info.steps -= Utility::StepReductionFactor;
    }
    void Movement::MovePurposely(MovementInfo &info)
    {
    }
    void Movement::MoveToPoint(sf::Vector2f)
    {
    }

    void Movement::UpdateMovementOperation(NFResolution16 id, Evolution::Movement::MovementOperation operation)
    {
        std::cout << __func__ << " Org: " << id << " Operation: " << static_cast<int>(operation) << std::endl;
        auto org = m_matrix->GetEntity(m_organismsMovementInfo[id].organismId);
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
            // org->setFillColor(sf::Color::Red);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToGroup:
            // org->setFillColor(sf::Color::Green);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToIgnore:
            // org->setFillColor(sf::Color::Cyan);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToFight:
            // org->setFillColor(sf::Color::Yellow);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToRun:
            // org->setFillColor(sf::Color::Magenta);
            break;
        }
    }
}