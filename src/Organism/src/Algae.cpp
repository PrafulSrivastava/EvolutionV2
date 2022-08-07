#include "Algae.hpp"

namespace Evolution::Organism
{
    Algae::Algae()
    {

        m_species = Species::ALGAE;
        m_attributes.energy = 100;
        m_attributes.speed = 2;
        m_attributes.stamina = 100;
        m_attributes.visionConeAngle = 45;
        m_attributes.visionDepth = 10;
        m_attributes.aggression = 10;
        m_attributes.socializing = 100;
    }

    void Algae::OnCollision(Species species)
    {
        if (species != m_species)
        {
        }
    }
    void Algae::Spawn()
    {
        setPosition(200, 200);
        setFillColor(sf::Color::Green);
        setRadius(4);
    }
    void Algae::Destroy()
    {
    }

    void Algae::RunMainLoop()
    {
    }

}