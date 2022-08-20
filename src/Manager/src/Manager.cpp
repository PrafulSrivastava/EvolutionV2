#include "Manager.hpp"
#include "Movement.hpp"
#include "IConfig.hpp"

#include "SingleCelledOrganism.hpp"
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
        CUtility::RegisterAllEnums();
        m_matrix = std::make_shared<EntityMatrix>(m_window);
        m_movement = std::make_shared<Movement>(m_matrix);
    }

    bool Manager::IsInVision(EntityId viewer, EntityId viewee)
    {
        bool inVision = false;
        auto viewerPos = m_matrix->GetEntity(viewer)->getPosition();
        auto vieweePos = m_matrix->GetEntity(viewee)->getPosition();

        auto res = std::sqrt(std::pow((vieweePos.x - viewerPos.x), 2) + std::pow((vieweePos.y - viewerPos.y), 2));
        if (res <= m_matrix->GetEntity(viewer)->GetAttributes()->visionDepth)
        {
            inVision = true;
            m_matrix->GetEntity(viewee)->SetCurrentPos(m_matrix->GetEntity(viewee)->getPosition());
        }
        return inVision;
    }

    bool Manager::HasCollided(EntityId viewer, EntityId viewee)
    {
        // TODO
        return false;
    }

    void Manager::Init()
    {

        std::shared_ptr<Evolution::Organism::IOrganismEntity> bacteria;
        std::shared_ptr<Evolution::Organism::IOrganismEntity> SingleCelledOrganism;

        // for (int i = 0; i < OrganismCount; i++)
        // {
        //     std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(static_cast<Organism::OrganismType>(CUtility::GetRandomValueInRange(0, 2)));
        //     AddEntity(org);
        // }
        for (int i = 0; i < CarnivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::OrganismType::CARNIVORE);
            AddEntity(org);
        }
        for (int i = 0; i < HerbivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::OrganismType::HERBIVORE);
            AddEntity(org);
        }
        for (int i = 0; i < OmnivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::OrganismType::OMNIVORE);
            AddEntity(org);
        }
    }

    void Manager::AddEntity(std::shared_ptr<Evolution::Organism::IOrganismEntity> org)
    {
        auto id = m_matrix->AddEntity(org);
        org->SetEntityId(id);
        org->GetAttributes()->label = CUtility::GenerateLabels(org->GetAttributes()->id);
        org->Spawn();
        m_movement->RegisterToMove(id, Evolution::Movement::MovementType::Randomly);
    }

    void Manager::RunMainLoop()
    {
        for (auto i : m_matrix->GetEntityMatrix())
        {
            for (auto j : m_matrix->GetEntityMatrix())
            {
                if (i.first == j.first)
                {
                    continue;
                }

                if (IsInVision(i.first, j.first))
                {
                    if (m_matrix->GetPriority(i.first, j.first) == INT16_MIN)
                    {
                        // std::cout << "Add:  Priority of: " << j.first << " for: " << i.first << " " << m_matrix->GetPriority(i.first, j.first) << std::endl;

                        m_matrix->SetTargetEncounteredInfo(i.first, j.first);
                        auto mostPriorityTargetId = m_matrix->CalculateMostPriorityTarget(i.first);
                        m_matrix->GetEntity(i.first)->SetMostPriorityTarget(mostPriorityTargetId);
                        // std::cout << "Added" << std::endl;
#ifdef LOG
                        // std::cout << "Setting Most Priority Target for Organism Id: " << i.first << " to: " << mostPriorityTargetId << std::endl;
#endif

                        m_matrix->GetEntity(i.first)->OnEncounter(m_matrix->GetEntity(i.first)->GetAttributes(), m_matrix->GetEntity(j.first)->GetAttributes());
                    }
                }
                else if (m_matrix->GetPriority(i.first, j.first) != INT16_MIN)
                {
                    // std::cout << "Reset:  Priority of: " << j.first << " for: " << i.first << " " << m_matrix->GetPriority(i.first, j.first) << std::endl;

                    m_matrix->ResetPriority(i.first, j.first);

                    m_matrix->GetEntity(i.first)->RemoveIfNotInVision(j.first);
                }

                if (HasCollided(i.first, j.first))
                {
                    m_matrix->GetEntity(i.first)->OnCollision(m_matrix->GetEntity(j.first)->GetAttributes());
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

            m_movement->Move();

            RunMainLoop();

            m_matrix->RunMainLoop();

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