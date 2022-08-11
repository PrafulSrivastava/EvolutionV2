#include "Movement.hpp"
#include "IConfig.hpp"

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
        for (auto &info : m_organismsMovementInfo)
        {
            switch (info.type)
            {
            case Evolution::Movement::MovementType::Randomly:
                MoveRandomly(info);
                break;
            case Evolution::Movement::MovementType::Purposely:
                MovePurposely(info);
                break;
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
}