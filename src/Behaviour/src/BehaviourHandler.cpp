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
            std::cout << __func__ << " New Target: " << m_mostPriorityTarget << " Reaction: " << static_cast<int>(m_organismsInView[m_mostPriorityTarget].reaction) << std::endl;

            reaction = m_organismsInView[m_mostPriorityTarget].reaction;

            auto operations = Reaction::GetInstance().React(m_type, reaction);
            m_reactionCb(operations);
        }
    }
}