#include "EntityMatrix.hpp"

namespace Evolution::Manager
{
    EntityMatrix::EntityMatrix()
    {
    }

    EntityMatrix::EntityId EntityMatrix::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        m_entityMatrix[++m_entityId];
        m_organismList.push_back(org);

        return m_entityId;
    }

    std::shared_ptr<Evolution::Organism::IOrganismEntity> EntityMatrix::GetEntity(const EntityMatrix::EntityId &id)
    {
        return m_organismList[id];
    }

    void EntityMatrix::RemoveEntity(const EntityMatrix::EntityId &org)
    {
        m_entityMatrix.erase(org);
        m_organismList.erase(m_organismList.begin() + org);
    }

    void EntityMatrix::SetTargetEncounteredInfo(const EntityMatrix::EntityId &org, const EntityMatrix::EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            itorg->second.insert({target, FetchPriority(org, target)});
        }
    }

    void EntityMatrix::RemoveTargetEncounteredInfo(const EntityMatrix::EntityId &org, const EntityMatrix::EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        itorg->second.erase(target);
    }

    EntityMatrix::Priority
    EntityMatrix::FetchPriority(const EntityMatrix::EntityId &org, const EntityMatrix::EntityId &target)
    {
        Priority priority;

        auto orgInfo = m_organismList[org]->GetAttributes();
        auto targetInfo = m_organismList[target]->GetAttributes();

        Resolution dSpeed = targetInfo->speed - orgInfo->speed;
        Resolution dEnergy = targetInfo->energy - orgInfo->energy;
        Resolution dStamina = targetInfo->stamina - orgInfo->stamina;
        Resolution dAggression = targetInfo->aggression - orgInfo->aggression;

        switch (m_organismList[target]->GetAttributes()->type)
        {
        case Organism::OrganismType::CARNIVORE:
        {
            priority = 0.3 * (dSpeed + dStamina) - 0.7 * (dEnergy + dAggression);
            break;
        }

        case Organism::OrganismType::HERBIVORE:
        {
            priority = 0.5 * (dSpeed + dStamina) + 0.5 * (dEnergy + dAggression);
            break;
        }

        case Organism::OrganismType::OMNIVORE:
        {
            priority = 0.4 * (dSpeed + dStamina) - 0.6 * (dEnergy + dAggression);
            break;
        }

        default:
            break;
        }

        return priority * 10;
    }

    NFResolution32 EntityMatrix::GetEntityCount()
    {
        return m_entityId + 1;
    }

    void EntityMatrix::Shutdown()
    {
        for (auto it : m_organismList)
        {
            it->Destroy();
        }
        m_organismList.clear();
        m_entityMatrix.clear();
    }
}