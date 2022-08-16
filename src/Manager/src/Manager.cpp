#include "Manager.hpp"
#include "Movement.hpp"
#include "IConfig.hpp"
#include "Bacteria.hpp"
#include "Algae.hpp"
#include "CUtility.hpp"
#include "BehaviourHandler.hpp"
#include <math.h>

namespace Evolution::Manager
{
    Manager::Manager()
    {
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(Evolution::Utility::Width, Evolution::Utility::Height), Evolution::Utility::WindowName);
        CUtility::Init(m_window);
        m_matrix = std::make_shared<EntityMatrix>();
        m_movement = std::make_shared<Movement>(m_matrix);
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
            viewee->SetCurrentPos(viewee->getPosition());
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

        for (int i = 0; i < 5; i++)
        {
            if (CUtility::HeadsOrTails() == Utility::Choice::HEADS)
            {
                std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::Algae>();
                AddEntity(org);
            }
            else
            {
                std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::Bacteria>();
                AddEntity(org);
            }
        }
    }

    void Manager::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        auto id = m_matrix->AddEntity(org);
        org->SetEntityId(id);
        org->Spawn();
        m_movement->RegisterToMove(id, Evolution::Movement::MovementType::Randomly);
    }

    void Manager::RunMainLoop()
    {
        for (int i = 0; i < m_matrix->GetEntityCount(); i++)
        {
            for (int j = 0; j < m_matrix->GetEntityCount(); j++)
            {
                if (i == j)
                {
                    continue;
                }

                if (IsInVision(m_matrix->GetEntity(i), m_matrix->GetEntity(j)))
                {
                    m_matrix->GetEntity(i)->OnEncounter(m_matrix->GetEntity(i)->GetAttributes(), m_matrix->GetEntity(j)->GetAttributes());
                }

                if (HasCollided(m_matrix->GetEntity(i), m_matrix->GetEntity(j)))
                {
                    m_matrix->GetEntity(i)->OnCollision(m_matrix->GetEntity(j)->GetAttributes());
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
            for (int i = 0; i < m_matrix->GetEntityCount(); i++)
            {
                m_matrix->GetEntity(i)->RunMainLoop();
                m_window->draw(*(m_matrix->GetEntity(i)));
                CUtility::ShowVisionInfo(m_matrix->GetEntity(i)->GetAttributes()->visionDepth, m_matrix->GetEntity(i)->GetAttributes()->visionConeAngle, m_matrix->GetEntity(i)->getPosition(), m_matrix->GetEntity(i)->getRotation());
            }

            m_window->display();
        }
    }

    void Manager::Shutdown()
    {
        m_movement.reset();
        m_window.reset();
        m_matrix->Shutdown();
    }
}