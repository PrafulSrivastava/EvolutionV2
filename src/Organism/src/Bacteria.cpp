#include "Bacteria.hpp"

namespace Evolution::Organism
{
    Bacteria::Bacteria()
    {
        m_species = Species::BACTERIA;
        m_attributes.energy = 100;
        m_attributes.speed = 2;
        m_attributes.stamina = 100;
        m_attributes.visionConeAngle = 45;
        m_attributes.visionDepth = 10;
        m_attributes.aggression = 10;
        m_attributes.socializing = 100;
    }

    void Bacteria::OnCollision(Species species)
    {
        if (species != m_species)
        {
        }
    }
    void Bacteria::Spawn()
    {
        // setPosition(CUtility::GetRandomValueInRange(Position::MIN_VALUE, Position::MAX_VALUE), CUtility::GetRandomValueInRange(Position::MIN_VALUE, Position::MAX_VALUE));
        setPosition(300, 300);
        setFillColor(sf::Color::Red);
        setRadius(4);
    }
    void Bacteria::Destroy()
    {
    }

    void Bacteria::RunMainLoop()
    {
    }

}