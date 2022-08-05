#include "Bacteria.hpp"

namespace Evolution::Organism
{
    Bacteria::Bacteria()
    {
        m_species = Species::BACTERIA;
        m_attributes.m_energy = 100;
        m_attributes.m_speed = 2;
        m_attributes.m_stamina = 100;
        m_attributes.m_vision = 45;
    }

    void Bacteria::OnCollision(Species species)
    {
        if (species != m_species)
        {
        }
    }
    void Bacteria::Spawn()
    {
        setPosition(400, 300);
        setFillColor(sf::Color::Green);
        setRadius(4);
    }
    void Bacteria::Destroy()
    {
    }

    void Bacteria::RunMainLoop()
    {
    }

}