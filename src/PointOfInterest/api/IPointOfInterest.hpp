// #ifndef IPOINTOFINTERESTENTITY_HPP
// #define IPOINTOFINTERESTENTITY_HPP

// #include "IEntity.hpp"
// #include "IConfig.hpp"

// namespace Evolution
// {
//     namespace PointOfInterest
//     {
//         enum class PointOfInterestType : uint8_t
//         {
//             INVALID = 254,
//             POND = 0
//         };

//         struct Attributes
//         {
//             Resolution m_speed{0};
//             Resolution m_vision{0};
//             Resolution m_stamina{0};
//             Resolution m_energy{0};
//         };

//         class IPointOfInterestEntity : public CEntityWrapper<sf::CircleShape>
//         {
//         public:
//             Attributes GetAttributes() const
//             {
//                 return m_attributes;
//             }

//         protected:
//             void OnEncounter();

//             Attributes m_attributes;
//             PointOfInterestType m_foodType;
//         };
//     }
// }

// #endif