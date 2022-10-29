#include "EntityMatrix.hpp"
#include "CUtility.hpp"

namespace Evolution::Manager
{
    EntityMatrix::EntityMatrix(std::shared_ptr<sf::RenderWindow> window) : m_window(window)
    {
    }

    EntityId EntityMatrix::AddEntity(std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>> org)
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

    std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>> EntityMatrix::GetEntity(const EntityId &id)
    {

        Debug(if (m_organismList.find(id) == m_organismList.end()) {
            return nullptr;
        });

        return m_organismList[id];
    }

    void EntityMatrix::RemoveEntity(const EntityId &id)
    {
        m_entityMatrix.erase(id);

        for (auto &item : m_entityMatrix)
        {
            auto itorg = item.second.find(id);
            if (itorg != item.second.end())
            {
                item.second.erase(itorg);
            }
        }

        auto itorg = m_organismList.find(id);
        if (itorg != m_organismList.end())
        {
            m_organismList.erase(itorg);
        }

        for (auto &org : m_organismList)
        {
            org.second->RemoveIfNotInVision(id);
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

    Priority EntityMatrix::FetchPriority(const EntityId &org, const EntityId &target)
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

            case Organism::SpeciesType::CARNIVORE:
            {
                typePriority += 100;
                break;
            }

            case Organism::SpeciesType::POI:
            {
                if (targetInfo->subType == Organism::SpeciesSubType::VEGETATION)
                {
                    if (orgInfo->type != Organism::SpeciesType::CARNIVORE)
                    {
                        typePriority += 70;
                    }
                }
                break;
            }

            case Organism::SpeciesType::HERBIVORE:
            {
                typePriority += 100;
                break;
            }

            case Organism::SpeciesType::OMNIVORE:
            {
                typePriority += 50;
                break;
            }

            default:
                break;
            }
        }

        Log(Log::DEBUG, __func__, "Org:", org, "Type:", pEnum(orgInfo->type));
        Log(Log::DEBUG, __func__, "Target:", target, "Type:", pEnum(targetInfo->type));
        Log(Log::DEBUG, __func__, "Type Priority:", typePriority);

        // Threat offset
        if (targetInfo->type != Organism::SpeciesType::POI)
        {
            priority += 0.35 * (dAggression + dEnergy) + 0.15 * (dSpeed + dStamina);
        }
        else if (targetInfo->subType == Organism::SpeciesSubType::VEGETATION && orgInfo->type != Organism::SpeciesType::CARNIVORE)
        {
            priority += 0.5 * (dEnergy + dStamina);
        }

        Log(Log::DEBUG, __func__, "Initial Priority:", priority);

        priority = 0.5 * priority + 0.5 * typePriority;

        Log(Log::DEBUG, __func__, "Priority:", priority);

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

    void EntityMatrix::FlipVisionInfo()
    {
        m_isVisionInfoOn = !m_isVisionInfoOn;
    }

    void EntityMatrix::RunMainLoop()
    {
        for (auto org : m_organismList)
        {
            org.second->RunMainLoop();
            m_window->draw(*org.second);

            if (m_isVisionInfoOn)
            {
                Debug(CUtility::ShowVisionInfo(org.second->GetAttributes()->visionDepth, org.second->GetAttributes()->visionConeAngle, org.second->getPosition(), org.second->getRotation());
                      CUtility::AddLabels(org.second->GetAttributes()->label, org.second->getPosition()));
            }
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