#ifndef IPOINTOFINTERESTENTITY_HPP
#define IPOINTOFINTERESTENTITY_HPP

#include "IEntity.hpp"
#include "IBehaviourHandler.hpp"
#include "IConfig.hpp"

namespace Evolution
{
    namespace PointOfInterest
    {

        class IPointOfInterestEntity : public CEntityWrapper<sf::CircleShape>
        {
        public:
            std::shared_ptr<Evolution::Organism::Attributes> GetAttributes() const override
            {
                return m_attributes;
            }

            NFResolution32 GetEntityId() override
            {
                return m_attributes->id;
            }

        protected:
            std::shared_ptr<Evolution::Organism::Attributes> m_attributes;
        };
    }
}

#endif