#ifndef IFOODENTITY_HPP
#define IFOODENTITY_HPP

#include "IEntity.hpp"
#include "IConfig.hpp"

namespace Evolution
{
    namespace Food
    {
        enum class FoodType : uint8_t
        {
            INVALID = 200,
            VEG = 0,
            NONVEG = 1
        };

        struct FoodContent
        {
            Resolution carbContent{0};
            Resolution fatContent{0};
            Resolution protienContent{0};
            Resolution waterContent{0};
        };

        class IFoodEntity : public IEntity
        {
        public:
            FoodType GetFoodType() const
            {
                return m_foodType;
            }

            void SetFoodType(FoodType type, FoodContent food)
            {
                m_foodType = type;
                m_foodContent = food;
            }

            Resolution GetNutrition()
            {
                return (Nutrition::PROTEIN * m_foodContent.protienContent) + (Nutrition::CARBON * m_foodContent.carbContent) + (Nutrition::FAT * m_foodContent.fatContent) + (Nutrition::WATER * m_foodContent.waterContent);
            }

            Resolution GetStamina()
            {
                return (Stamina::WATER * m_foodContent.waterContent) + (Stamina::PROTEIN * m_foodContent.protienContent) + (Stamina::FAT * m_foodContent.fatContent) + (Stamina::CARBON * m_foodContent.carbContent);
            }

        protected:
            FoodType m_foodType;
            FoodContent m_foodContent;
        };
    }
}

#endif