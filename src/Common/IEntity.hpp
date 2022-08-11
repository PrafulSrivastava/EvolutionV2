#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "IConfig.hpp"
#include "CUtility.hpp"

#ifdef UNIT_TEST
#include <gtest/gtest.h>
#endif

namespace Evolution
{
    enum Species : uint8_t
    {
        INVALID = 200,
        VACOULE = 0,
        BACTERIA = 1,
        ALGAE = 2
    };

    template <typename Entity>
    class CEntityWrapper : public Entity
    {
    public:
        CEntityWrapper();
        ~CEntityWrapper() = default;
        CEntityWrapper(const CEntityWrapper &) = default;
        CEntityWrapper &operator=(const CEntityWrapper &) = default;
        CEntityWrapper(CEntityWrapper &&) = default;
        CEntityWrapper &operator=(CEntityWrapper &&) = default;

        int32_t GetEntityId();
        bool IsAlive();
        void SetLiveStatus(bool);
        virtual void OnCollision(Species);
        virtual void Spawn();
        virtual void Destroy();
        virtual void RunMainLoop();

        Species GetSpecies()
        {
            return m_species;
        }

    protected:
        int32_t m_Id{};
        Evolution::shortBool m_isActive;
        sf::Vector2f m_coordinates;
        Species m_species;

#ifdef DEBUG
    private:
        std::vector<sf::Lines> m_stats;
        std::vector<sf::Lines> m_visionCone;
#endif

#ifdef UNIT_TEST
        FRIEND_TEST(VacuoleTest, SampleTest);
#endif
    };

    template <typename Entity>
    CEntityWrapper<Entity>::CEntityWrapper()
        : m_Id(0)
    {
        m_isActive.set(0);
    }

    template <typename Entity>
    bool CEntityWrapper<Entity>::IsAlive()
    {
        return m_isActive.all();
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::SetLiveStatus(bool status)
    {
        (status) ? m_isActive.set(0) : m_isActive.reset(0);
    }

    template <typename Entity>
    int32_t CEntityWrapper<Entity>::GetEntityId()
    {
        return m_Id;
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::OnCollision(Species)
    {
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::Spawn()
    {
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::Destroy()
    {
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::RunMainLoop()
    {
    }
}

#endif