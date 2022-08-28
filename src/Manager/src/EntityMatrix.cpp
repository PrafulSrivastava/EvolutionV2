#include "EntityMatrix.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{
    EntityMatrix::EntityMatrix(std::shared_ptr<sf::RenderWindow> window) : m_window(window)
    {
    }

    EntityId EntityMatrix::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        m_entityMatrix[++m_entityId];
        m_organismList[m_entityId] = org;

        return m_entityId;
    }

    void EntityMatrix::ResetPriority(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            itorg->second[target] = INT16_MIN;
        }
    }

    Priority EntityMatrix::GetPriority(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            auto itTarget = itorg->second.find(target);
            if (itTarget != itorg->second.end())
            {
                return itTarget->second;
            }
        }
        return INT16_MIN;
    }

    EntityId EntityMatrix::CalculateMostPriorityTarget(const Evolution::Manager::EntityId &id)
    {
        Priority max = INT32_MIN;
        EntityId idMax;

        Log(Log::DEBUG, "Organism Id:", id, "Organism Type:", pEnum(m_organismList[id]->GetAttributes()->type));

        for (auto target : m_entityMatrix[id])
        {
            Log(Log::VERBOSE, "Target Id:", target.first, "Priority:", target.second, "Target Type:", pEnum(m_organismList[target.first]->GetAttributes()->type));

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

        for (auto &item : m_entityMatrix)
        {
            auto itorg = item.second.find(org);
            if (itorg != item.second.end())
            {
                item.second.erase(itorg);
            }
        }

        auto itorg = m_organismList.find(org);
        if (itorg != m_organismList.end())
        {
            m_organismList.erase(itorg);
        }
    }

    void EntityMatrix::SetTargetEncounteredInfo(const EntityId &org, const EntityId &target)
    {
        auto itorg = m_entityMatrix.find(org);
        if (itorg != m_entityMatrix.end())
        {
            auto newPrio = FetchPriority(org, target);
            itorg->second[target] = newPrio;
            Log(Log::DEBUG, "New Priority of", target, "for", org, "is", newPrio);
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
        priority += (0.5 * priority + 0.5 * (typePriority));

        return priority;
    }

    NFResolution32 EntityMatrix::GetEntityCount()
    {
        return m_entityId + 1;
    }

    std::unordered_map<EntityId, std::unordered_map<EntityId, Priority>> EntityMatrix::GetEntityMatrix()
    {
        return m_entityMatrix;
    }

    void EntityMatrix::RunMainLoop()
    {
        for (auto org : m_organismList)
        {
            org.second->RunMainLoop();
            m_window->draw(*org.second);

#ifdef DEBUG_MODE
            CUtility::ShowVisionInfo(org.second->GetAttributes()->visionDepth, org.second->GetAttributes()->visionConeAngle, org.second->getPosition(), org.second->getRotation());
            CUtility::AddLabels(org.second->GetAttributes()->label, org.second->getPosition());
#endif
        }
    }

    void EntityMatrix::Shutdown()
    {
        for (auto it : m_organismList)
        {
            it.second->Destroy();
        }
        m_organismList.clear();
        m_entityMatrix.clear();
    }
}