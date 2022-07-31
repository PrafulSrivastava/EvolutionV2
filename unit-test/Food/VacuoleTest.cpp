#include "Vacuole.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "memory"

using ::testing::_;
using ::testing::Return;

namespace Evolution
{
    class VacuoleTest : public ::testing::Test
    {
    protected:
        virtual void SetUp()
        {
            entity = std::make_shared<Food::Vacuole>();
        }

        virtual void TearDown()
        {
            entity.reset();
        }

    public:
        std::shared_ptr<IEntity> entity;
    };

    TEST_F(VacuoleTest, SampleTest)
    {
        EXPECT_EQ(entity->m_species, Species::VACOULE);
    }
}
