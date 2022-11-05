#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "IManager.hpp"
#include "IMovement.hpp"
#include "IOrganismEntity.hpp"
#include "IPointOfInterest.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include "EntityMatrix.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

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
        void RunGameDebugLoop();
        void RunGameLoop();
        void AddEntity(std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>>);
        void Init();
        void Shutdown() override;

    private:
        bool IsInVision(EntityId viewer, EntityId viewee);
        bool HasCollided(EntityId viewer, EntityId viewee);
        void UpdateLifeTime();
        void Reproduce();

        std::shared_ptr<IMovement> m_movement{nullptr};
        std::shared_ptr<EntityMatrix> m_matrix{nullptr};
        std::shared_ptr<std::thread> m_debugThread;
        sf::Event m_event;
        std::mutex m_mtx;
        std::chrono::time_point<std::chrono::system_clock> m_startTime, m_spanTime;
        std::shared_ptr<Timer<std::chrono::seconds>> m_timer;
    };
}

#endif