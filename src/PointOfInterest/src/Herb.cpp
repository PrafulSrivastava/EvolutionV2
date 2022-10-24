#include "Herb.hpp"
#include "CUtility.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::PointOfInterest
{
    Herb::Herb(Organism::SpeciesType type)
    {
        m_attributes = std::make_shared<Organism::Attributes>(CUtility::GenerateRandomAttributes(type));

        m_attributes->type = type;
        m_attributes->subType = Organism::SpeciesSubType::VEGETATION;
    }

    void Herb::SetEntityId(NFResolution32 id)
    {
        m_attributes->id = id;
    }

    void Herb::Spawn()
    {
        CUtility::SetRandomSpawnStats(*this, m_attributes->type);
    }

    void Herb::Destroy()
    {
        m_attributes.reset();
    }

    void Herb::RunMainLoop()
    {
    }

}