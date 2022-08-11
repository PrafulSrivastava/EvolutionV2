#include "CUtility.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Behaviour
{
    BehaviourHandler::BehaviourHandler()
    {
    }

    sf::Vector2f BehaviourHandler::FindClosestOrganism(sf::Vector2f orgPos)
    {
        Resolution minDist = INT32_MAX;
        sf::Vector2f result;

        // for (auto it : m_organismsInView)
        // {
        //     auto dis = CUtility::GetDistanceBetweenPoints(orgPos, it.second->getPosition());
        //     if (dis <= minDist)
        //     {
        //         minDist = dis;
        //         result = it.second->getPosition();
        //     }
        // }

        // m_hasNewPoi = false;
        // m_hasDesination = true;

        return result;
    }

    void BehaviourHandler::RunMainLoop()
    {
        if (m_hasNewPoi)
        {
            // m_destination = FindClosestOrganism(sf::Vector2f orgPos);
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

    void BehaviourHandler::FightBack()
    {
    }

    void BehaviourHandler::Group()
    {
        if (!m_targetReached)
        {
        }
        else
        {
            // Grouping protocol
            // Maybe exchange of Info, so it will bond
        }
    }

    void BehaviourHandler::Kill()
    {
    }

    void BehaviourHandler::Ignore()
    {
    }

    void BehaviourHandler::Run()
    {
    }
}
