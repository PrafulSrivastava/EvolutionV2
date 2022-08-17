#ifndef ENTITY_MATRIX_HPP
#define ENTITY_MATRIX_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include "IOrganismEntity.hpp"
#include "IConfig.hpp"

namespace Evolution::Manager
{
    class EntityMatrix
    {

    public:
        EntityMatrix();
        ~EntityMatrix() = default;
        EntityMatrix(const EntityMatrix &) = default;
        EntityMatrix &operator=(const EntityMatrix &) = default;
        EntityMatrix(EntityMatrix &&) = default;
        EntityMatrix &operator=(EntityMatrix &&) = default;

        NFResolution32 GetEntityCount();
        void Shutdown();

        void SetTargetEncounteredInfo(const EntityId &, const EntityId &);
        void RemoveTargetEncounteredInfo(const EntityId &, const EntityId &);
        EntityId CalculateMostPriorityTarget(Evolution::Manager::EntityId id);

        EntityId AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity>);
        std::shared_ptr<Evolution::Organism::IOrganismEntity> GetEntity(const EntityId &);
        void RemoveEntity(const EntityId &org);

    private:
        std::unordered_map<EntityId, std::unordered_map<EntityId, Priority>> m_entityMatrix;
        std::vector<std::shared_ptr<Evolution::Organism::IOrganismEntity>> m_organismList;
        EntityId m_entityId{-1};

        Priority FetchPriority(const EntityId &, const EntityId &);
    };
}

#endif