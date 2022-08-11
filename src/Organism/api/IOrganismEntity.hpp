#ifndef IORGANISMENTITY_HPP
#define IORGANISMENTITY_HPP

#include "IEntity.hpp"
#include "IBehaviourHandler.hpp"
#include "IConfig.hpp"
#include <memory>

namespace Evolution
{
    namespace Organism
    {

        class IOrganismEntity : public CEntityWrapper<sf::CircleShape>
        {
        public:
            std::shared_ptr<Attributes> GetAttributes() const
            {
                return m_attributes;
            }

            void OnCollision(Attributes targetAttributes)
            {
                m_behaviour->OnCollision(targetAttributes);
            }

            void OnEncounter(Attributes orgAttributes, Attributes targetAttributes)
            {
                // auto reaction = Reaction::GetInstance().React(m_organism, organismEncountered);

                // // Need to replace with priority queue
                // m_organismsInView.push_back({reaction, organismEncountered});
                // m_hasNewPoi = true;
                m_behaviour->OnEncounter(orgAttributes, targetAttributes);
            }

        protected:
            void OnEncounter();
            std::shared_ptr<Evolution::Behaviour::IBehaviourHandler> m_behaviour;
            std::shared_ptr<Attributes> m_attributes;
            OrganismType m_type;
        };
    }
}

#endif