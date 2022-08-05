#include "Manager.hpp"
#include "IConfig.hpp"
#include "Bacteria.hpp"
#include "Carnivore.hpp"
#include <math.h>

namespace Evolution::Manager
{
    Manager::Manager()
    {
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(Evolution::Utility::Width, Evolution::Utility::Height), Evolution::Utility::WindowName);
    }

    bool Manager::IsInVision(std::shared_ptr<Evolution::Behaviour::IBehaviourEntity> viewer, std::shared_ptr<Evolution::Behaviour::IBehaviourEntity> viewee)
    {
        bool inVision = false;
        auto viewerPos = viewer->GetEntity()->getPosition();
        auto vieweePos = viewee->GetEntity()->getPosition();

        auto res = std::sqrt(std::pow((vieweePos.x - viewerPos.x), 2) + std::pow((vieweePos.y - viewerPos.y), 2));
        if (res <= viewer->GetVision().visionDepth)
        {
            inVision = true;
        }
        return inVision;
    }

    void Manager::Init()
    {
        std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::Bacteria>();

        std::shared_ptr<Evolution::Behaviour::IBehaviourEntity>
            bacteria = std::make_shared<Evolution::Behaviour::Carnivore>(org);

        AddEntity(bacteria);
    }

    void Manager::AddEntity(std::shared_ptr<Evolution::Behaviour::IBehaviourEntity> org)
    {
        org->GetEntity()->Spawn();
        m_organisms.push_back(org);
    }

    void Manager::RunMainLoop()
    {
        for (int i = 0; i < m_organisms.size(); i++)
        {
            for (int j = 0; j < m_organisms.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }

                if (IsInVision(m_organisms[i], m_organisms[j]))
                {
                    m_organisms[i]->OnEncounter(m_organisms[j]->GetEntity());
                }
            }
        }
    }

    void Manager::RunGameLoop()
    {
        sf::Event event;
        uint8_t tempVal = 0;
        m_window->setFramerateLimit(Utility::FrameLimit);

        while (m_window->isOpen())
        {
            m_window->clear(sf::Color::Black);
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window->close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        m_window->close();
                    }
                }
            }

            RunMainLoop();
            for (int i = 0; i < m_organisms.size(); i++)
            {
                m_organisms[i]->RunMainLoop();
                m_window->draw(*(m_organisms[i]->GetEntity()));
            }

            m_window->display();
        }
    }
}