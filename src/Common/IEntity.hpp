#ifndef IENTITY_HPP
#define IENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#ifdef UNIT_TEST
#include <gtest/gtest.h>
#endif

namespace Evolution
{
    enum Species : uint8_t
    {
        INVALID = 200,
        VACOULE = 0,
        BACTERIA = 1
    };

    class IEntity
    {
    public:
        virtual void OnCollision(Species) = 0;
        virtual void Spawn() = 0;
        virtual void Destroy() = 0;

    protected:
        sf::Vector2f m_coordinates;
        Species m_species;

#ifdef UNIT_TEST
        FRIEND_TEST(VacuoleTest, SampleTest);
#endif
    };
}

#endif