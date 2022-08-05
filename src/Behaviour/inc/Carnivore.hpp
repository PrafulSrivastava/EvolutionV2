#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP

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

    class Carnivore : public IBehaviourEntity
    {
    public:
        Carnivore(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism);
        ~Carnivore() = default;
        Carnivore(const Carnivore &) = default;
        Carnivore &operator=(const Carnivore &) = default;
        Carnivore(Carnivore &&) = default;
        Carnivore &operator=(Carnivore &&) = default;

        void RunMainLoop();

    private:
        sf::Vector2f FindClosestOrganism();
        MapOfPOIs m_poi;
        sf::Vector2f m_destination;
        bool m_hasDesination{false};
    };
}

#endif