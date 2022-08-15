#include "Algae.hpp"
#include "BehaviourHandler.hpp"
#include "CUtility.hpp"

namespace Evolution::Organism
{
    Algae::Algae()
    {
        m_species = Species::ALGAE;
        m_attributes = std::make_shared<Attributes>(CUtility::GenerateRandomAttributes());
        if (rand() % 2 == 0)
        {
            m_attributes->type = OrganismType::OMNIVORE;
        }
        else
        {
            m_attributes->type = OrganismType::HERBIVORE;
        }

        m_behaviour = std::make_shared<Evolution::Behaviour::BehaviourHandler>(m_attributes->type);
        m_behaviour->RegisterForReaction(std::bind(&Algae::OnReaction, this, std::placeholders::_1));
    }

    void Algae::SetEntityId(NFResolution32 id)
    {
        m_attributes->id = id;
    }

    void Algae::Spawn()
    {
        CUtility::SetRandomSpawnStats(*this);
    }

    void Algae::Destroy()
    {
        m_attributes.reset();
        m_behaviour.reset();
    }

    void Algae::RunMainLoop()
    {
        m_behaviour->RunMainLoop(getPosition());
    }

}