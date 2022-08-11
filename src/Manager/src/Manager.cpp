#include "Manager.hpp"
#include "Movement.hpp"
#include "IConfig.hpp"
#include "Bacteria.hpp"
#include "Algae.hpp"
#include "BehaviourHandler.hpp"
#include <math.h>

namespace Evolution::Manager
{
    Manager::Manager()
    {
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(Evolution::Utility::Width, Evolution::Utility::Height), Evolution::Utility::WindowName);
        CUtility::Init(m_window);
        m_movement = std::make_shared<Movement>();
    }

    bool Manager::IsInVision(std::shared_ptr<Evolution::Organism::IOrganismEntity> viewer, std::shared_ptr<Evolution::Organism::IOrganismEntity> viewee)
    {
        // TODO: Need to add Matrix logic
        // viewerId and targetId
        // mat[viewerId]
        // mat[targetId]
        bool inVision = false;
        auto viewerPos = viewer->getPosition();
        auto vieweePos = viewee->getPosition();

        auto res = std::sqrt(std::pow((vieweePos.x - viewerPos.x), 2) + std::pow((vieweePos.y - viewerPos.y), 2));
        if (res <= viewer->GetAttributes()->visionDepth)
        {
            inVision = true;
        }
        return inVision;
    }

    bool Manager::HasCollided(std::shared_ptr<Evolution::Organism::IOrganismEntity> viewer, std::shared_ptr<Evolution::Organism::IOrganismEntity> viewee)
    {
        // TODO
        return false;
    }

    void Manager::Init()
    {

        std::shared_ptr<Evolution::Organism::IOrganismEntity> bacteria;
        std::shared_ptr<Evolution::Organism::IOrganismEntity> algae;

        for (int i = 0; i < 33; i++)
        {
            if (rand() % 2 == 0)
            {
                std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::Bacteria>();
                m_movement->RegisterToMove(org, Evolution::Movement::MovementType::Randomly);
                AddEntity(org);
            }
            else
            {
                std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::Algae>();
                m_movement->RegisterToMove(org, Evolution::Movement::MovementType::Randomly);
                AddEntity(org);
            }
        }
    }

    void Manager::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        org->Spawn();
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
                    m_organisms[i]->OnEncounter(*(m_organisms[i]->GetAttributes()), *(m_organisms[j]->GetAttributes()));
                }

                if (HasCollided(m_organisms[i], m_organisms[j]))
                {
                    m_organisms[i]->OnCollision(*(m_organisms[j]->GetAttributes()));
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
            m_movement->Move();
            for (int i = 0; i < m_organisms.size(); i++)
            {
                m_organisms[i]->RunMainLoop();
                m_window->draw(*(m_organisms[i]));
                CUtility::ShowVisionInfo(m_organisms[i]->GetAttributes()->visionDepth, m_organisms[i]->GetAttributes()->visionConeAngle, m_organisms[i]->getPosition(), m_organisms[i]->getRotation());
            }

            m_window->display();
        }
    }
}