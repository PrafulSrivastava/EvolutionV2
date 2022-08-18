#include "EntityMatrix.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{
    EntityMatrix::EntityMatrix()
    {
    }

    EntityId EntityMatrix::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        m_entityMatrix[++m_entityId];
        m_organismList.push_back(org);

        return m_entityId;
    }

    void EntityMatrix::ResetPriority(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            itorg->second.insert({target, INT16_MIN});
        }
    }

    EntityId EntityMatrix::CalculateMostPriorityTarget(Evolution::Manager::EntityId id)
    {
        Priority max = INT32_MIN;
        EntityId idMax;

        std::cout << "Organism Id:" << id << " Organism Type: " << pEnum(m_organismList[id]->GetAttributes()->type) << std::endl;

        for (auto target : m_entityMatrix[id])
        {
            std::cout << "Target Id:" << target.first << " Priority: " << target.second << " Target Type: " << pEnum(m_organismList[target.first]->GetAttributes()->type) << std::endl;
            if (target.second >= max)
            {
                max = target.second;
                idMax = target.first;
            }
        }

        return idMax;
    }

    std::shared_ptr<Evolution::Organism::IOrganismEntity> EntityMatrix::GetEntity(const EntityId &id)
    {
        return m_organismList[id];
    }

    void EntityMatrix::RemoveEntity(const EntityId &org)
    {
        m_entityMatrix.erase(org);
        m_organismList.erase(m_organismList.begin() + org);
    }

    void EntityMatrix::SetTargetEncounteredInfo(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            itorg->second.insert({target, FetchPriority(org, target)});
        }
    }

    void EntityMatrix::RemoveTargetEncounteredInfo(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        itorg->second.erase(target);
    }

    Priority
    EntityMatrix::FetchPriority(const EntityId &org, const EntityId &target)
    {
        Priority priority{0}, typePriority{0};

        auto orgInfo = m_organismList[org]->GetAttributes();
        auto targetInfo = m_organismList[target]->GetAttributes();

        Resolution dSpeed = targetInfo->speed - orgInfo->speed;
        Resolution dEnergy = targetInfo->energy - orgInfo->energy;
        Resolution dStamina = targetInfo->stamina - orgInfo->stamina;
        Resolution dAggression = targetInfo->aggression - orgInfo->aggression;

        if (orgInfo->type != targetInfo->type)
        {
            switch (targetInfo->type)
            {
            case Organism::OrganismType::CARNIVORE:
            {
                typePriority += 100;
                break;
            }

            case Organism::OrganismType::HERBIVORE:
            {
                typePriority += 100;
                break;
            }

            case Organism::OrganismType::OMNIVORE:
            {
                typePriority += 50;
                break;
            }

            default:
                break;
            }
        }

        priority += 0.35 * (dAggression + dEnergy) + 0.15 * (dSpeed + dStamina);
        priority += (0.50 * priority + 0.5 * (typePriority));

        return priority;
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