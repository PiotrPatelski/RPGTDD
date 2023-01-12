#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CoreBuilder.hpp>
#include <Window.hpp>
#include <Clock.hpp>
#include <StateMachine.hpp>

namespace Core
{


struct CoreBuilderTest : public testing::Test
{
    std::unique_ptr<ICoreBuilder> sut = std::make_unique<CoreBuilder>();
};

TEST_F(CoreBuilderTest, coreBuilderCreatesWindow)
{
    auto window = sut->createWindow();
    ASSERT_NE(nullptr, window);
    EXPECT_EQ(typeid(std::unique_ptr<IWindow>), typeid(window));
}

TEST_F(CoreBuilderTest, coreBuilderCreatesClock)
{
    auto clock = sut->createClock();
    ASSERT_NE(nullptr, clock);
    EXPECT_EQ(typeid(std::unique_ptr<IClock>), typeid(clock));
}

TEST_F(CoreBuilderTest, coreBuilderCreatesStateMachine)
{
    auto stateMachine = sut->createStateMachine();
    ASSERT_NE(nullptr, stateMachine);
    EXPECT_EQ(typeid(std::unique_ptr<IStateMachine>), typeid(stateMachine));
}

}