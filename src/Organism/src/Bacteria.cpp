#include "Bacteria.hpp"
#include "BehaviourHandler.hpp"
#include "CUtility.hpp"

namespace Evolution::Organism
{
    Bacteria::Bacteria()
    {
        m_species = Species::BACTERIA;
        m_attributes = std::make_shared<Attributes>(CUtility::GenerateRandomAttributes());
        if (CUtility::HeadsOrTails() == Utility::Choice::HEADS)
        {
            m_attributes->type = OrganismType::OMNIVORE;
        }
        else
        {
            m_attributes->type = OrganismType::CARNIVORE;
        }
        m_behaviour = std::make_shared<Evolution::Behaviour::BehaviourHandler>(m_attributes->type);
        m_behaviour->RegisterForReaction(std::bind(&Bacteria::OnReaction, this, std::placeholders::_1));
    }

    void Bacteria::SetEntityId(NFResolution32 id)
    {
        m_attributes->id = id;
    }

    void Bacteria::Spawn()
    {
        CUtility::SetRandomSpawnStats(*this);
    }

    void Bacteria::Destroy()
    {
        m_attributes.reset();
        m_behaviour.reset();
    }

    void Bacteria::RunMainLoop()
    {
        m_behaviour->RunMainLoop(getPosition());
    }

}