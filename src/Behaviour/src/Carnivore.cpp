#include "Utility.hpp"
#include "Carnivore.hpp"

namespace Evolution::Behaviour
{
    Carnivore::Carnivore(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism)
    {
        m_vision.visionConeAngle = 45;
        m_vision.visionDepth = 10;
        m_organism = organism;

        m_organism->setPosition(Evolution::Utility::Width / 2, Evolution::Utility::Height / 2);
    }

    sf::Vector2f Carnivore::FindClosestOrganism()
    {
        Resolution minDist = INT32_MAX;
        sf::Vector2f result;

        for (auto itr = m_organismsInView.begin(); itr != m_organismsInView.end(); itr++)
        {
            auto dis = CUtility::GetDistanceBetweenPoints(m_organism->getPosition(), (*itr)->getPosition());
            if (dis <= minDist)
            {
                minDist = dis;
                result = (*itr)->getPosition();
            }
        }

        m_hasNewPoi = false;
        m_hasDesination = true;

        return result;
    }

    void Carnivore::RunMainLoop()
    {
        // Start from origin
        // Move Random steps in Random Direction
        if (!m_hasDesination)
        {

            auto steps = rand() % 10;

            switch (rand() % 4)
            {
            case 0:
                m_organism->move(0, -1 * m_organism->GetAttributes().m_speed * steps);
                break;
            case 1:
                m_organism->move(0, m_organism->GetAttributes().m_speed * steps);
                break;
            case 2:
                m_organism->move(m_organism->GetAttributes().m_speed * steps * -1, 0);
                break;
            case 3:
                m_organism->move(m_organism->GetAttributes().m_speed * steps, 0);
                break;
            }
        }

        // What is a POI
        // if food was spotted at x, y. Then POI is a circle of radius of 'r' with x,y as origin
        // if another food is found in the same circle
        // priority of the circle increases.
        // Find mean origin and reset the POI origin.

        // Find POIs
        if (m_hasNewPoi)
        {

            m_destination = FindClosestOrganism();

            // Move to POIs
            // Increment Priority on every visit which is fruitful
            // Fruitful: If food was spotted
        }

        if (m_hasDesination)
        {

            auto currentPos = m_organism->getPosition();
            Resolution xToMove = m_destination.x - currentPos.x;
            Resolution yToMove = m_destination.y - currentPos.y;

            if (xToMove == 0 && yToMove == 0)
            {
                m_hasDesination = false;
            }

            m_organism->move(std::abs(xToMove) * m_organism->GetAttributes().m_speed / xToMove, std::abs(yToMove) * m_organism->GetAttributes().m_speed / yToMove);
        }

        // Stay for a while
        // set visited flag to true
        // Set Home to max priority
        // Move to another POI
    }
}

// behaviours
// Grouping
// Aggression

// Start from origin
// Move Random steps in Random Direction

// What is a POI
// if food was spotted at x, y. Then POI is a circle of radius of 'r' with x,y as origin
// if another food is found in the same circle
// priority of the circle increases.
// Find mean origin and reset the POI origin.
// Find POIs
// Move to POIs

// Every Herbivore needs

// Increment Priority on every visit which is fruitful
// Fruitful: If food was spotted
// Stay for a while
// set visited flag to true
// Set Home to max prior