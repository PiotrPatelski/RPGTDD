#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachine.hpp>
#include "StateMock.hpp"
#include "WindowMock.hpp"


namespace Core
{

using namespace ::testing;

struct StateMachineTest : public testing::Test
{
    sf::Vector2i dummyMousePos{0,0};
    std::shared_ptr<NiceMock<States::StateMock>> activeState = std::make_shared<NiceMock<States::StateMock>>();
    std::unique_ptr<NiceMock<States::StateMock>> nextState = std::make_unique<NiceMock<States::StateMock>>();
    std::unique_ptr<IStateMachine> sut = std::make_unique<StateMachine>();
    NiceMock<WindowMock> window;
};

TEST_F(StateMachineTest, stateMachineHasFinishedItsWorkWhenNoStatesAreToHandle)
{
    ASSERT_FALSE(sut->isAnyStateActive());
}

TEST_F(StateMachineTest, stateMachineHasNotFinishedItsWorkWhenStateIsActive)
{
    sut->setState(activeState);
    ASSERT_TRUE(sut->isAnyStateActive());
}

TEST_F(StateMachineTest, currentStateIsUpdatedWhenStateMachineUpdates)
{
    EXPECT_CALL(*activeState, update(A<const Core::IWindow&>(), A<float>()));
    sut->setState(activeState);
    sut->update(window, 0.f);
}

TEST_F(StateMachineTest, stateMachineChecksIfActiveStateIsDoneWhenUpdated)
{
    EXPECT_CALL(*activeState, isReadyToChange());
    sut->setState(activeState);
    sut->update(window, 0.f);
}

TEST_F(StateMachineTest, stateMachineReadsNextStateWhenCurrentStateIsDone)
{

    ON_CALL(*activeState, isReadyToChange()).WillByDefault(Return(true));
    EXPECT_CALL(*activeState, getNextState()).WillOnce(Return(ByMove(std::move(nextState))));
    sut->setState(activeState);
    sut->update(window, 0.f);
}

TEST_F(StateMachineTest, stateMachineDoesNotReadNextStateWhenCurrentStateIsNotDone)
{
    ON_CALL(*activeState, isReadyToChange()).WillByDefault(Return(false));
    EXPECT_CALL(*activeState, getNextState()).Times(0);
    sut->setState(activeState);
    sut->update(window, 0.f);
}

TEST_F(StateMachineTest, stateMachineReturnsValidStateWhenRunsOne)
{
    sut->setState(activeState);
    EXPECT_NE(sut->getCurrentState(), nullptr);
}

}