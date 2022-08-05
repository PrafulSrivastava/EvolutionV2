#ifndef ICONFIG_HPP
#define ICONFIG_HPP

#include <bitset>

namespace Evolution
{
    using Resolution = int;
    using shortBool = std::bitset<1>;

    namespace Nutrition
    {
        constexpr auto PROTEIN = 0.4;
        constexpr auto CARBON = 0.4;
        constexpr auto FAT = 0.4;
        constexpr auto WATER = 0.4;
    }

    namespace Stamina
    {
        constexpr auto PROTEIN = 0.2;
        constexpr auto CARBON = 0.05;
        constexpr auto FAT = 0.05;
        constexpr auto WATER = 0.7;
    }

    namespace Utility
    {
        constexpr auto Height = 600;
        constexpr auto FrameLimit = 120;
        constexpr auto Width = 800;
        constexpr auto WindowName = "EVOLUTION";

    }

}

#endif