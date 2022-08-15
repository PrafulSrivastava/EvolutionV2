#ifndef BEHAVIOUR_HANDLER_HPP
#define BEHAVIOUR_HANDLER_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include "IBehaviourHandler.hpp"
#include "IMovement.hpp"
#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Evolution::Behaviour
{
    using PriorityPair = std::pair<NFResolution, bool>;
    using MapOfPOIs = std::map<sf::Vector2f, PriorityPair>;

    class BehaviourHandler : public IBehaviourHandler
    {
    public:
        // BehaviourHandler() = default;
        BehaviourHandler(Organism::OrganismType);
        ~BehaviourHandler() = default;
        BehaviourHandler(const BehaviourHandler &) = default;
        BehaviourHandler &operator=(const BehaviourHandler &) = default;
        BehaviourHandler(BehaviourHandler &&) = default;
        BehaviourHandler &operator=(BehaviourHandler &&) = default;

        void RunMainLoop(sf::Vector2f) override;

    private:
        NFResolution FindClosestOrganism(sf::Vector2f);
        MapOfPOIs m_poi;
        sf::Vector2f m_destination;
    };
}

#endif