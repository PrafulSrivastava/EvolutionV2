#include "Movement.hpp"
#include "IConfig.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{

    int16_t Movement::RegisterToMove(std::shared_ptr<Evolution::Organism::IOrganismEntity> org, Evolution::Movement::MovementType type)
    {
        MovementInfo info;
        info.organism = org;
        info.type = type;
        info.steps = 0;
        info.hemisphere = 0;
        info.quadrant = 0;

        m_organismsMovementInfo.push_back(info);
        return ++m_subscriptionId;
    }

    void Movement::UpdateMovement(int16_t id, Evolution::Movement::MovementType type)
    {
        m_organismsMovementInfo[id].type = type;
    }

    void Movement::UnRegisterToMove(int16_t id)
    {
        m_organismsMovementInfo.erase(m_organismsMovementInfo.begin() + id);
    }

    void Movement::Move()
    {
        for (NFResolution i = 0; i < m_organismsMovementInfo.size(); i++)
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

            for (auto operation : m_organismsMovementInfo[i].organism->FetchMovementOperations())
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

        auto attributes = info.organism->GetAttributes();
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
            info.organism->setRotation(angle);
        }

        auto ratio = CUtility::GetMovementRatio(info.organism->getRotation());
        auto yToMove = ratio.y * attributes->speed;
        auto xToMove = ratio.x * attributes->speed;
        auto newPos = sf::Vector2f(info.organism->getPosition().x + xToMove, info.organism->getPosition().y + yToMove);
        ResetOnBoundryEncounter(newPos);

        info.organism->setPosition(newPos);
        info.steps -= 1;
    }
    void Movement::MovePurposely(MovementInfo &info)
    {
    }
    void Movement::MoveToPoint(sf::Vector2f)
    {
    }

    void Movement::UpdateMovementOperation(int16_t id, Evolution::Movement::MovementOperation operation)
    {
        std::cout << __func__ << " For " << id << std::endl;

        auto &org = m_organismsMovementInfo[id].organism;
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