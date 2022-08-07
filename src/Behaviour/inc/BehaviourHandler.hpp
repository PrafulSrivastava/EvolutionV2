#ifndef BEHAVIOUR_HANDLER_HPP
#define BEHAVIOUR_HANDLER_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include "IBehaviourEntity.hpp"
#include "IOrganismEntity.hpp"
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Evolution::Behaviour
{
    using PriorityPair = std::pair<int32_t, bool>;
    using MapOfPOIs = std::map<sf::Vector2f, PriorityPair>;

    class BehaviourHandler : public IBehaviourEntity
    {
    public:
        // BehaviourHandler() = default;
        BehaviourHandler(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism);
        ~BehaviourHandler() = default;
        BehaviourHandler(const BehaviourHandler &) = default;
        BehaviourHandler &operator=(const BehaviourHandler &) = default;
        BehaviourHandler(BehaviourHandler &&) = default;
        BehaviourHandler &operator=(BehaviourHandler &&) = default;

        void RunMainLoop();

    private:
        sf::Vector2f FindClosestOrganism();

        void Move();
        void Group();
        void Kill();
        void FightBack();
        void Ignore();
        void Run();

        MapOfPOIs m_poi;
        sf::Vector2f m_destination;
        bool m_hasDesination{false};
    };
}

#endif