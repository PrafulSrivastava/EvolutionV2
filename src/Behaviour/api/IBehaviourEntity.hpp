#ifndef IBEHAVIOURENTITY_HPP
#define IBEHAVIOURENTITY_HPP

#include "IConfig.hpp"
#include "IOrganismEntity.hpp"
#include "Reaction.hpp"

namespace Evolution
{
    namespace Behaviour
    {

        struct Vision
        {
            Resolution visionDepth{0};
            Resolution visionConeAngle{0};
        };

        class IBehaviourEntity
        {
        public:
            virtual void RunMainLoop()
            {
            }

            Vision GetVision()
            {
                return m_vision;
            }

            std::shared_ptr<Evolution::Organism::IOrganismEntity> GetEntity()
            {
                return m_organism;
            }

            void OnCollision(std::shared_ptr<Evolution::Organism::IOrganismEntity> organismEncountered)
            {
                // TO DO
            }

            void OnEncounter(std::shared_ptr<Evolution::Organism::IOrganismEntity> organismEncountered)
            {
                auto reaction = Reaction::GetInstance().React(m_organism, organismEncountered);

                // Need to replace with priority queue
                m_organismsInView.push_back({reaction, organismEncountered});
                m_hasNewPoi = true;
            }

        protected:
            Vision m_vision;
            bool m_hasNewPoi{false}, m_targetReached{false};
            std::shared_ptr<Evolution::Organism::IOrganismEntity> m_organism, m_target;
            std::vector<std::pair<ReactionType, std::shared_ptr<Evolution::Organism::IOrganismEntity>>> m_organismsInView;
            Resolution m_steps{0}, m_direction{0}, m_speedOffset{0}, m_speedFactor{1};
            ReactionType m_reaction;
        };
    }
}

#endif