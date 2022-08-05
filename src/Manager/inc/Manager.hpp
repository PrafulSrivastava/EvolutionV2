#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "IManager.hpp"
#include "IBehaviourEntity.hpp"
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
        void AddEntity(std::shared_ptr<Evolution::Behaviour::IBehaviourEntity>);
        void Init();

    private:
        bool IsInVision(std::shared_ptr<Evolution::Behaviour::IBehaviourEntity> viewer, std::shared_ptr<Evolution::Behaviour::IBehaviourEntity> viewee);
        std::vector<std::shared_ptr<Evolution::Behaviour::IBehaviourEntity>> m_organisms;
    };
}

#endif