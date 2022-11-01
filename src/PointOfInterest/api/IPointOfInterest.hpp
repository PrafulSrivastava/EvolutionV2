#ifndef IPOINTOFINTERESTENTITY_HPP
#define IPOINTOFINTERESTENTITY_HPP

#include "IEntity.hpp"
#include "IBehaviourHandler.hpp"
#include "IConfig.hpp"
#include "CUtility.hpp"

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

            std::string ToString()
            {

                std::string stats{};

                stats += "#) ";
                stats += "ID: ";
                stats += std::to_string(m_attributes->id);
                stats += "\t";

                stats += "#) ";
                stats += "Type: ";
                stats += pEnum(m_attributes->type);
                stats += "\t";

                stats += "#) ";
                stats += "Sub Type: ";
                stats += pEnum(m_attributes->subType);
                stats += "\n\n";

                stats += "#) ";
                stats += "Position: ";
                stats += std::to_string(getPosition().x);
                stats += ", ";
                stats += std::to_string(getPosition().y);
                stats += "\n\n";

                // stats += "Aggression: ";
                // stats += std::to_string(m_attributes->aggression);
                // stats += "\n";

                // stats += "Energy: ";
                // stats += std::to_string(m_attributes->energy);
                // stats += "\n";

                // stats += "Speed: ";
                // stats += std::to_string(m_attributes->speed);
                // stats += "\n";

                // stats += "Stamina: ";
                // stats += std::to_string(m_attributes->stamina);
                // stats += "\n";

                // stats += "Vision Depth: ";
                // stats += std::to_string(m_attributes->visionDepth);
                // stats += "\n";

                // stats += "Vision Cone Angle: ";
                // stats += std::to_string(m_attributes->visionConeAngle);
                // stats += "\n";

                Log(Log::DEBUG, stats);

                return stats;
            }

        protected:
            std::shared_ptr<Evolution::Organism::Attributes> m_attributes;
        };
    }
}

#endif