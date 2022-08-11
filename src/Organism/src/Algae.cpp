#include "Algae.hpp"
#include "BehaviourHandler.hpp"

namespace Evolution::Organism
{
    Algae::Algae()
    {

        m_species = Species::ALGAE;
        m_attributes = std::make_shared<Attributes>();
        m_attributes->energy = 100;
        m_attributes->speed = rand() % 5 + 1;
        m_attributes->stamina = 100;
        m_attributes->aggression = rand() % 200;
        m_attributes->visionConeAngle = rand() % 46 + 45;
        m_attributes->visionDepth = rand() % 20 + 30;

        m_behaviour = std::make_shared<Evolution::Behaviour::BehaviourHandler>();
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
        setPointCount(rand() % 100 + 3);
        setFillColor(sf::Color::Green);
        setRadius(rand() % 20 + 4);
        setOrigin(getRadius(), getRadius());
        setRotation(rand() % 360);
    }
    void Algae::Destroy()
    {
    }

    void Algae::RunMainLoop()
    {
    }

}