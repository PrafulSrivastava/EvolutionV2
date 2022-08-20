#include "SingleCelledOrganism.hpp"
#include "BehaviourHandler.hpp"
#include "CUtility.hpp"

namespace Evolution::Organism
{
    SingleCelledOrganism::SingleCelledOrganism(Organism::OrganismType type)
    {
        m_species = Species::SingleCelledOrganism;
        m_attributes = std::make_shared<Attributes>(CUtility::GenerateRandomAttributes(type));
        m_attributes->type = type;
        m_behaviour = std::make_shared<Evolution::Behaviour::BehaviourHandler>(m_attributes->type);
        m_behaviour->RegisterForReaction(std::bind(&SingleCelledOrganism::OnReaction, this, std::placeholders::_1));
    }

    void SingleCelledOrganism::SetEntityId(NFResolution32 id)
    {
        m_attributes->id = id;
        m_behaviour->SetOrgId(m_attributes->id);
    }

    void SingleCelledOrganism::Spawn()
    {
        CUtility::SetRandomSpawnStats(*this, m_attributes->type);
    }

    void SingleCelledOrganism::Destroy()
    {
        m_attributes.reset();
        m_behaviour.reset();
    }

    void SingleCelledOrganism::RunMainLoop()
    {
        m_behaviour->RunMainLoop(getPosition());
    }

}