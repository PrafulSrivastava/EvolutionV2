#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "IConfig.hpp"

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
        SingleCelledOrganism = 2,
        Herb = 3
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

        virtual NFResolution32 GetEntityId();
        virtual void SetEntityId(NFResolution32 id);
        virtual bool IsAlive();
        virtual void SetLiveStatus(bool);
        virtual void OnCollision(Species);
        virtual void Spawn();
        virtual void Destroy();
        virtual void RunMainLoop();
        virtual std::shared_ptr<Organism::Attributes> GetAttributes() const { return nullptr; }
        virtual void RemoveIfNotInVision(const Manager::EntityId &id) {}
        virtual void OnCollision(std::shared_ptr<Organism::Attributes> targetAttributes) {}
        virtual void OnEncounter(std::shared_ptr<Organism::Attributes> orgAttributes, std::shared_ptr<Organism::Attributes> targetAttributes) {}
        virtual void SetMostPriorityTarget(Manager::EntityId index) {}
        virtual void OnReaction(Movement::TargetMovementInfo operations) {}
        virtual void SetCurrentPos(sf::Vector2f pos) {}
        virtual Movement::TargetMovementInfo FetchMovementOperations() { return Movement::TargetMovementInfo(); };

        Species GetSpecies()
        {
            return m_species;
        }

    protected:
        NFResolution32 m_Id{-1};
        Evolution::shortBool m_isActive{0};
        sf::Vector2f m_coordinates;
        Species m_species{Species::INVALID};

#ifdef UNIT_TEST
    public:
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
    void CEntityWrapper<Entity>::SetEntityId(NFResolution32 id)
    {
        m_Id = id;
    }

    template <typename Entity>
    void CEntityWrapper<Entity>::SetLiveStatus(bool status)
    {
        (status) ? m_isActive.set(0) : m_isActive.reset(0);
    }

    template <typename Entity>
    NFResolution32 CEntityWrapper<Entity>::GetEntityId()
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