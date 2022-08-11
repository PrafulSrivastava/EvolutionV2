#include "Bacteria.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Organism
{
    Bacteria::Bacteria()
    {
        m_species = Species::BACTERIA;
        m_attributes = std::make_shared<Attributes>();
        m_attributes->energy = 100;
        m_attributes->speed = rand() % 5 + 1;
        m_attributes->stamina = 100;
        m_attributes->aggression = rand() % 200;
        m_attributes->visionConeAngle = rand() % 46 + 45;
        m_attributes->visionDepth = rand() % 20 + 30;
        m_behaviour = std::make_shared<Evolution::Behaviour::BehaviourHandler>();
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
        setPointCount(rand() % 100 + 3);

        setRadius(rand() % 20 + 4);
        setOrigin(getRadius(), getRadius());

        setRotation(rand() % 360);
    }
    void Bacteria::Destroy()
    {
    }

    void Bacteria::RunMainLoop()
    {
    }

}