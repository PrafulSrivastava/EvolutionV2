#include "Utility.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Behaviour
{
    BehaviourHandler::BehaviourHandler(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism)
    {
        // TO DO: Need to make constexpr and randomize
        m_vision.visionConeAngle = 45;
        m_vision.visionDepth = 200;

        m_organism = organism;

        m_organism->setPosition(Evolution::Utility::Width / 2, Evolution::Utility::Height / 2);
    }

    sf::Vector2f BehaviourHandler::FindClosestOrganism()
    {
        Resolution minDist = INT32_MAX;
        sf::Vector2f result;

        for (auto it : m_organismsInView)
        {
            auto dis = CUtility::GetDistanceBetweenPoints(m_organism->getPosition(), it.second->getPosition());
            if (dis <= minDist && it.second != m_target)
            {
                minDist = dis;
                m_target = it.second;
                result = it.second->getPosition();
                m_reaction = it.first;
            }
        }

        m_hasNewPoi = false;
        m_hasDesination = true;

        return result;
    }

    void BehaviourHandler::RunMainLoop()
    {
        // Start from origin
        // Move Random steps in Random Direction
        if (m_steps <= 0)
        {
            m_steps = rand() % 20;
            m_direction = rand() % 4;
        }

        if (!m_hasDesination)
        {
            switch (rand() % 4)
            {
            case 0:
                m_organism->move(0, -1 * m_organism->GetAttributes().speed * m_steps);
                break;
            case 1:
                m_organism->move(0, m_organism->GetAttributes().speed * m_steps);
                break;
            case 2:
                m_organism->move(m_organism->GetAttributes().speed * m_steps * -1, 0);
                break;
            case 3:
                m_organism->move(m_organism->GetAttributes().speed * m_steps, 0);
                break;
            }
        }

        if (m_hasNewPoi)
        {
            m_destination = FindClosestOrganism();
        }

        if (m_hasDesination)
        {
            switch (m_reaction)
            {
            case ReactionType::KILL:
                Kill();
                break;

            case ReactionType::IGNORE:
                Ignore();
                break;

            case ReactionType::RUN:
                Run();
                break;

            case ReactionType::GROUP:
                Group();
                break;

            default:
                Ignore();
                break;
            }
        }
    }

    void BehaviourHandler::Move()
    {
        // Movement Logic
        // speed = speed * Factor + offset
        auto speed = GetEntity()->GetAttributes().speed * m_speedFactor + m_speedOffset;
    }

    // This one is when someone attacks and to save itself
    void BehaviourHandler::FightBack()
    {
    }

    void BehaviourHandler::Group()
    {
        if (!m_targetReached)
        {
            // Move Normally
            m_speedFactor = 1;
            m_speedOffset = 1;
            Move();
        }
        else
        {
            // Grouping protocol
            // Maybe exchange of Info, so it will bond
        }
    }

    void BehaviourHandler::Kill()
    {
        // TO MOVE Fast and stealthy
        m_speedFactor = 10;
        m_speedOffset = 5;
        Move();
    }

    void BehaviourHandler::Ignore()
    {
    }

    void BehaviourHandler::Run()
    {
    }
}
