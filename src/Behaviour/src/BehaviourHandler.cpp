#include "CUtility.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Behaviour
{
    BehaviourHandler::BehaviourHandler(Organism::OrganismType type)
    {
        m_type = type;
    }

    NFResolution32 BehaviourHandler::FindClosestOrganism(sf::Vector2f orgPos)
    {
        std::lock_guard<std::mutex> lck(m_mtx);

        Resolution minDist = INT32_MAX;
        NFResolution32 result;

        for (auto &it : m_organismsInView)
        {
            auto dis = CUtility::GetDistanceBetweenPoints(orgPos, it.second.position);

            if (dis <= minDist)
            {
                minDist = dis;
                result = it.first;
            }
        }

        m_hasNewPoi = false;

        return result;
    }

    void BehaviourHandler::RunMainLoop(sf::Vector2f orgPos)
    {
        auto reaction = ReactionType::INVALID;
        if (m_hasNewPoi)
        {
            auto index = FindClosestOrganism(orgPos);
            reaction = m_organismsInView[index].reaction;

            auto operations = Reaction::GetInstance().React(m_type, reaction);
            m_reactionCb(operations);
        }
    }
}