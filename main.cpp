#include "Vacuole.hpp"
#include "Bacteria.hpp"

int main()
{
    Evolution::IEntity *entity;

    entity = new Evolution::Food::Vacuole();
    entity->Spawn();
    entity = new Evolution::Organism::Bacteria();
    entity->Spawn();

    return 0;
}