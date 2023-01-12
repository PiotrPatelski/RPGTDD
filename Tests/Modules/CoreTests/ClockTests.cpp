#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Clock.hpp>

namespace Core
{

struct ClockTest : public testing::Test
{
    std::unique_ptr<IClock> sut = std::make_unique<Clock>();
};

TEST_F(ClockTest, deltaTimeIsUpdated)
{
    float startingTime = 0.f;
    ASSERT_EQ(sut->getDeltaTime(),startingTime);
    sut->updateDeltaTime();
    ASSERT_NE(sut->getDeltaTime(),startingTime);
}

}