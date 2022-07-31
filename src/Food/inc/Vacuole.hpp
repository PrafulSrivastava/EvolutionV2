#ifndef VACUOLE_HPP
#define VACUOLE_HPP

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include "IFoodEntity.hpp"

namespace Evolution::Food
{
    constexpr auto PROTEIN_CONTENT = 5;
    constexpr auto CARBON_CONTENT = 5;
    constexpr auto FAT_CONTENT = 5;
    constexpr auto WATER_CONTENT = 5;

    class Vacuole : public IFoodEntity
    {
    public:
        Vacuole();
        ~Vacuole();

        void OnCollision(Species) override;
        void Spawn() override;
        void Destroy() override;
    };
}

#endif