#ifndef IBEHAVIOURENTITY_HPP
#define IBEHAVIOURENTITY_HPP

#include "IConfig.hpp"
#include "IOrganismEntity.hpp"

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

            void OnEncounter(std::shared_ptr<Evolution::Organism::IOrganismEntity> organismEncountered)
            {
                m_organismsInView.push_back(organismEncountered);
                m_hasNewPoi = true;
            }

        protected:
            Vision m_vision;
            bool m_hasNewPoi{false};
            std::shared_ptr<Evolution::Organism::IOrganismEntity> m_organism;
            std::vector<std::shared_ptr<Evolution::Organism::IOrganismEntity>> m_organismsInView;
        };
    }
}

#endif