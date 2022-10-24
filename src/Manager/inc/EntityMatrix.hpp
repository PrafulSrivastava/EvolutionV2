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
        EntityMatrix(std::shared_ptr<sf::RenderWindow>);
        ~EntityMatrix() = default;
        EntityMatrix(const EntityMatrix &) = default;
        EntityMatrix &operator=(const EntityMatrix &) = default;
        EntityMatrix(EntityMatrix &&) = default;
        EntityMatrix &operator=(EntityMatrix &&) = default;

        NFResolution32 GetEntityCount();
        void Shutdown();

        void SetTargetEncounteredInfo(const EntityId &, const EntityId &);
        void RemoveTargetEncounteredInfo(const EntityId &, const EntityId &);
        EntityId CalculateMostPriorityTarget(const Evolution::Manager::EntityId &);

        EntityId AddEntity(std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>>);
        std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>> GetEntity(const EntityId &);
        void RemoveEntity(const EntityId &);
        void ResetPriority(const EntityId &, const EntityId &);
        Priority GetPriority(const EntityId &, const EntityId &);
        std::unordered_map<EntityId, std::unordered_map<EntityId, Priority>> GetEntityMatrix();
        void RunMainLoop();

    private:
        std::unordered_map<EntityId, std::unordered_map<EntityId, Priority>> m_entityMatrix;
        std::unordered_map<EntityId, std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>>> m_organismList;
        EntityId m_entityId{-1};

        Priority FetchPriority(const EntityId &, const EntityId &);
        std::shared_ptr<sf::RenderWindow> m_window;
    };
}

#endif