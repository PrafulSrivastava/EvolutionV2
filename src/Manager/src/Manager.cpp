#include "Manager.hpp"
#include "Movement.hpp"
#include "IConfig.hpp"

#include "SingleCelledOrganism.hpp"
#include "Herb.hpp"
#include "CUtility.hpp"
#include "BehaviourHandler.hpp"
#include <math.h>
#include <future>

namespace Evolution::Manager
{
    Manager::Manager()
    {
        m_window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(Evolution::Utility::Width, Evolution::Utility::Height), Evolution::Utility::WindowName);

        CUtility::RegisterAllEnums();
        m_matrix = std::make_shared<EntityMatrix>(m_window);
        m_movement = std::make_shared<Movement>(m_matrix);

        Debug(m_debugWindow = std::make_shared<sf::RenderWindow>(
                  sf::VideoMode(Evolution::Utility::WidthDebugWindow, Evolution::Utility::HeightDebugWindow), Evolution::Utility::DebugWindowName);
              m_debugThread = std::make_shared<std::thread>(&Manager::RunGameDebugLoop, this);
              m_debugThread->detach());

        Log(Log::DEBUG, "Main Thread");

        CUtility::Init(m_window, m_debugWindow);
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
        for (int i = 0; i < CarnivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::SpeciesType::CARNIVORE);
            AddEntity(org);
        }
        for (int i = 0; i < HerbivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::SpeciesType::HERBIVORE);
            AddEntity(org);
        }
        for (int i = 0; i < OmnivoreCount; i++)
        {
            std::shared_ptr<Evolution::Organism::IOrganismEntity> org = std::make_shared<Evolution::Organism::SingleCelledOrganism>(Organism::SpeciesType::OMNIVORE);
            AddEntity(org);
        }

        for (int i = 0; i < HerbCount; i++)
        {
            std::shared_ptr<Evolution::PointOfInterest::IPointOfInterestEntity> poi = std::make_shared<Evolution::PointOfInterest::Herb>(Organism::SpeciesType::POI);
            AddEntity(poi);
        }
    }

    void Manager::AddEntity(std::shared_ptr<Evolution::CEntityWrapper<sf::CircleShape>> org)
    {
        auto id = m_matrix->AddEntity(org);
        org->SetEntityId(id);
        org->GetAttributes()->label = CUtility::GenerateLabels(org->GetAttributes()->id);
        org->Spawn();

        if (org->GetAttributes()->type != Organism::SpeciesType::POI)
        {
            m_movement->RegisterToMove(id, Evolution::Movement::MovementType::Randomly);
        }
    }

    void Manager::RunMainLoop()
    {
        for (auto i : m_matrix->GetEntityMatrix())
        {
            for (auto j : m_matrix->GetEntityMatrix())
            {
                if (i.first == j.first || m_matrix->GetEntity(i.first)->GetAttributes()->type == Organism::SpeciesType::POI)
                {
                    continue;
                }

                if (IsInVision(i.first, j.first))
                {
                    if (m_matrix->GetPriority(i.first, j.first) == INT16_MIN)
                    {
                        m_matrix->SetTargetEncounteredInfo(i.first, j.first);
                        auto mostPriorityTargetId = m_matrix->CalculateMostPriorityTarget(i.first);
                        m_matrix->GetEntity(i.first)->SetMostPriorityTarget(mostPriorityTargetId);

                        m_matrix->GetEntity(i.first)->OnEncounter(m_matrix->GetEntity(i.first)->GetAttributes(), m_matrix->GetEntity(j.first)->GetAttributes());
                    }
                }
                else if (m_matrix->GetPriority(i.first, j.first) != INT16_MIN)
                {
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
        Log(Log::DEBUG, __func__);

        // sf::Event m_event;
        uint8_t tempVal = 0;
        m_window->setFramerateLimit(Utility::FrameLimit);
        NFResolution16 debugTarget{0};

        while (m_window->isOpen())
        {
            m_window->clear(sf::Color::Black);

            std::lock_guard<std::mutex> lck(m_mtx);
            {

                while (m_window->pollEvent(m_event))
                {
                    if (m_event.type == sf::Event::Closed)
                    {
                        m_window->close();
                        Debug(m_debugWindow->close());
                    }
                    if (m_event.type == sf::Event::KeyPressed)
                    {
                        if (m_event.key.code == sf::Keyboard::Escape)
                        {
                            m_window->close();
                            Debug(m_debugWindow->close());
                        }

                        Debug(
                            if (m_event.key.code == sf::Keyboard::V) {
                                m_matrix->FlipVisionInfo();
                            });
                    }
                    Debug(if (m_event.type == sf::Event::MouseMoved) {
                        auto pos = sf::Mouse::getPosition(*m_window);

                        for (auto entity : m_matrix->GetEntityMatrix())
                        {
                            if (m_matrix->GetEntity(entity.first) != nullptr)
                            {
                                if (CUtility::IsInCircumference(*(m_matrix->GetEntity(entity.first)), sf::Vector2f(pos.x, pos.y)))
                                {
                                    if (m_matrix->GetEntity(debugTarget) != nullptr)
                                        m_matrix->GetEntity(debugTarget)->setOutlineThickness(0);
                                    debugTarget = entity.first;
                                }
                            }
                        }
                    })
                }
            }

            m_movement->Move();

            RunMainLoop();

            m_matrix->RunMainLoop();

            m_window->display();

            Debug(m_debugWindow->clear(sf::Color::Black);

                  if (m_matrix->GetEntity(debugTarget) != nullptr) {
                      m_matrix->GetEntity(debugTarget)->setOutlineThickness(Utility::HighlightBoundry);
                      m_matrix->GetEntity(debugTarget)->setOutlineColor(Utility::HighlightColor);
                  } CUtility::DisplayEntityStats(m_matrix->GetEntity(debugTarget), m_movement->ToString(debugTarget));
                  m_debugWindow->display());
        }
    }

    void Manager::RunGameDebugLoop()
    {
        Log(Log::DEBUG, __func__);

        uint8_t tempVal = 0;
        m_debugWindow->setFramerateLimit(Utility::FrameLimit);

        while (m_debugWindow->isOpen())
        {
            std::lock_guard<std::mutex> lck(m_mtx);
            {
                while (m_debugWindow->pollEvent(m_event))
                {
                    if (m_event.type == sf::Event::Closed)
                    {
                        m_debugWindow->close();
                    }
                    if (m_event.type == sf::Event::KeyPressed)
                    {
                        if (m_event.key.code == sf::Keyboard::Escape)
                        {
                            m_debugWindow->close();
                        }
                    }
                }
            }
        }
    }

    void Manager::Shutdown()
    {
        m_movement.reset();
        m_window.reset();
        m_matrix->Shutdown();
    }
}