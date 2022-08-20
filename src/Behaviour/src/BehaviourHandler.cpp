#include "CUtility.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Behaviour
{
    BehaviourHandler::BehaviourHandler(Organism::OrganismType type)
    {
        m_type = type;
    }

    void BehaviourHandler::RunMainLoop(sf::Vector2f orgPos)
    {
        auto reaction = ReactionType::INVALID;
        if (m_hasNewPoi)
        {
            reaction = m_organismsInView[m_mostPriorityTarget].reaction;
            // std::cout << "New POI: " << m_mostPriorityTarget << " for : " << m_orgId << " " << pEnum(reaction) << std::endl;

            Movement::MovementAttribute operations = {Reaction::GetInstance().React(m_type, reaction), m_mostPriorityTarget};
            m_reactionCb(operations);
            m_hasNewPoi = false;
        }
    }
}