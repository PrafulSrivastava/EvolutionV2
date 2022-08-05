#include "Vacuole.hpp"
#include "Bacteria.hpp"

#include <iostream>
#include <memory>
#include <random>
#include <functional>
#include "IEntity.hpp"
#include "IConfig.hpp"

#include "IManager.hpp"
#include "Manager.hpp"
using namespace Evolution::Utility;

int main()
{
    srand(time(nullptr));
    Evolution::Manager::Manager obj;
    obj.Init();
    obj.RunGameLoop();
}