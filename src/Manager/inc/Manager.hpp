#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "IManager.hpp"
#include "IMovement.hpp"
#include "IOrganismEntity.hpp"
#include <vector>
#include <memory>
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
        bool IsInVision(std::shared_ptr<Evolution::Organism::IOrganismEntity> viewer, std::shared_ptr<Evolution::Organism::IOrganismEntity> viewee);
        bool HasCollided(std::shared_ptr<Evolution::Organism::IOrganismEntity> viewer, std::shared_ptr<Evolution::Organism::IOrganismEntity> viewee);

        std::vector<std::shared_ptr<Evolution::Organism::IOrganismEntity>> m_organisms;

        std::shared_ptr<IMovement> m_movement{nullptr};
        NFResolution m_ids{-1};
    };
}

#endif