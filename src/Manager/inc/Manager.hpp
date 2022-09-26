#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "IManager.hpp"
#include "IMovement.hpp"
#include "IOrganismEntity.hpp"
#include <vector>
#include <memory>
#include "EntityMatrix.hpp"
#include "Logger.hpp"

namespace Evolution::Manager
{
    class Manager : public IManager
    {
    public:
        Manager();
        ~Manager() = default;
        Manager(const Manager &) = default;
        Manager &operator=(const Manager &) = default;
        Manager(Manager &&) = default;
        Manager &operator=(Manager &&) = default;

        void RunMainLoop();
        void RunGameLoop();
        void AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity>);
        void Init();
        void Shutdown() override;

    private:
        bool IsInVision(EntityId viewer, EntityId viewee);
        bool HasCollided(EntityId viewer, EntityId viewee);
        std::shared_ptr<IMovement> m_movement{nullptr};
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
    };
}

#endif