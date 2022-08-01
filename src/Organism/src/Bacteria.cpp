#include "Bacteria.hpp"

namespace Evolution::Organism
{
    Bacteria::Bacteria()
    {
        m_species = Species::BACTERIA;
    }

    Bacteria::~Bacteria()
    {
    }

    void Bacteria::OnCollision(Species species)
    {
        if (species != m_species)
        {
        }
    }
    void Bacteria::Spawn()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void Bacteria::Destroy()
    {
    }
}