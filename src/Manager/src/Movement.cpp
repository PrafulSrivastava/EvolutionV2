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
        info.hemisphere = 0;
        info.quadrant = 0;

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
            info.steps = rand() % Evolution::Movement::MaxSteps + Evolution::Movement::MinSteps;
            auto hemisphereProbability = rand() % 100;

            if (hemisphereProbability >= 70)
            {
                if (info.hemisphere == 0)
                {

                    info.hemisphere = 1;
                }
                else
                {
                    info.hemisphere = 0;
                }
            }

            auto quadrantProbability = rand() & 100;

            if (quadrantProbability >= 70)
            {
                if (info.hemisphere == 0)
                {
                    info.quadrant = rand() % 2;
                }
                else
                {
                    info.quadrant = rand() % 2 + 2;
                }
            }

            auto angle = rand() % 90 + (90 * info.quadrant);
            m_matrix->GetEntity(info.organismId)->setRotation(angle);
        }

        auto ratio = CUtility::GetMovementRatio(m_matrix->GetEntity(info.organismId)->getRotation());
        auto yToMove = ratio.y * attributes->speed;
        auto xToMove = ratio.x * attributes->speed;
        auto newPos = sf::Vector2f(m_matrix->GetEntity(info.organismId)->getPosition().x + xToMove, m_matrix->GetEntity(info.organismId)->getPosition().y + yToMove);
        ResetOnBoundryEncounter(newPos);

        m_matrix->GetEntity(info.organismId)->setPosition(newPos);
        info.steps -= 1;
    }
    void Movement::MovePurposely(MovementInfo &info)
    {
    }
    void Movement::MoveToPoint(sf::Vector2f)
    {
    }

    void Movement::UpdateMovementOperation(NFResolution16 id, Evolution::Movement::MovementOperation operation)
    {
        std::cout << __func__ << " For " << id << std::endl;

        auto org = m_matrix->GetEntity(m_organismsMovementInfo[id].organismId);
        switch (operation)
        {
        case Evolution::Movement::MovementOperation::IncrementSpeed:
            std::cout << __func__ << " IncrementSpeed for " << id << " FROM : " << org->GetAttributes()->speed << std::endl;
            org->GetAttributes()->speed += 0.01;
            std::cout << __func__ << " TO: : " << org->GetAttributes()->speed << std::endl;

            break;
        case Evolution::Movement::MovementOperation::DecrementSpeed:
            std::cout << __func__ << " Decrement for " << id << " FROM : " << org->GetAttributes()->speed << std::endl;

            if (org->GetAttributes()->speed > 0.01)
            {
                org->GetAttributes()->speed -= 0.01;
            }
            std::cout << __func__ << " TO: : " << org->GetAttributes()->speed << std::endl;

            break;
        case Evolution::Movement::MovementOperation::RotateBy180:

            std::cout << __func__ << " Change Angle for " << id << " FROM : " << org->getRotation() << std::endl;
            org->setRotation(org->getRotation() + 180);
            std::cout << __func__ << " TO : " << org->getRotation() << std::endl;
            break;
        case Evolution::Movement::MovementOperation::RotateBy90:
            std::cout << __func__ << " Change Angle for " << id << " FROM : " << org->getRotation() << std::endl;

            org->setRotation(org->getRotation() + 90);
            std::cout << __func__ << " TO : " << org->getRotation() << std::endl;

            break;
        case Evolution::Movement::MovementOperation::RotateByRandom:
            std::cout << __func__ << " Change Angle for " << id << " FROM : " << org->getRotation() << std::endl;
            org->setRotation(org->getRotation() + rand() % 360);
            std::cout << __func__ << " TO : " << org->getRotation() << std::endl;
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToKill:
            std::cout << __func__ << "ChangeMotionToKill" << std::endl;

            org->setFillColor(sf::Color::Red);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToGroup:
            std::cout << __func__ << "ChangeMotionToGroup" << std::endl;

            org->setFillColor(sf::Color::Green);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToIgnore:
            std::cout << __func__ << "ChangeMotionToIgnore" << std::endl;

            org->setFillColor(sf::Color::Cyan);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToFight:
            std::cout << __func__ << "ChangeMotionToFight" << std::endl;

            org->setFillColor(sf::Color::Yellow);
            break;
        case Evolution::Movement::MovementOperation::ChangeMotionToRun:
            std::cout << __func__ << "ChangeMotionToRun" << std::endl;

            org->setFillColor(sf::Color::Magenta);
            break;
        }
    }
}