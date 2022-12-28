#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachine.h>
#include "StateMock.h"


namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::_;

struct StateMachineTest : public testing::Test
{
    sf::Vector2i dummyMousePos{0,0};
    std::shared_ptr<NiceMock<States::StateMock>> activeState = std::make_shared<NiceMock<States::StateMock>>();
    std::unique_ptr<NiceMock<States::StateMock>> nextState = std::make_unique<NiceMock<States::StateMock>>();
    std::unique_ptr<IStateMachine> sut = std::make_unique<StateMachine>();
};

TEST_F(StateMachineTest, stateMachineHasFinishedItsWorkWhenNoStatesAreToHandle)
{
    ASSERT_TRUE(sut->isNoStateActive());
}

TEST_F(StateMachineTest, stateMachineHasNotFinishedItsWorkWhenStateIsActive)
{
    sut->runState(activeState);
    ASSERT_FALSE(sut->isNoStateActive());
}

TEST_F(StateMachineTest, currentStateIsUpdatedWhenStateMachineUpdates)
{
    EXPECT_CALL(*activeState, update(_, _));
    sut->runState(activeState);
    sut->update(dummyMousePos, 0.f);
}

TEST_F(StateMachineTest, stateMachineChecksIfActiveStateIsDoneWhenUpdated)
{
    EXPECT_CALL(*activeState, isDone());
    sut->runState(activeState);
    sut->update(dummyMousePos, 0.f);
}

TEST_F(StateMachineTest, stateMachineReadsNextStateWhenCurrentStateIsDone)
{

    ON_CALL(*activeState, isDone()).WillByDefault(Return(true));
    EXPECT_CALL(*activeState, getNextState()).WillOnce(Return(ByMove(std::move(nextState))));
    sut->runState(activeState);
    sut->update(dummyMousePos, 0.f);
}

TEST_F(StateMachineTest, stateMachineDoesNotReadNextStateWhenCurrentStateIsNotDone)
{
    ON_CALL(*activeState, isDone()).WillByDefault(Return(false));
    EXPECT_CALL(*activeState, getNextState()).Times(0);
    sut->runState(activeState);
    sut->update(dummyMousePos, 0.f);
}

TEST_F(StateMachineTest, stateMachineReturnsValidStateWhenRunsOne)
{
    sut->runState(activeState);
    EXPECT_NE(sut->getCurrentState(), nullptr);
}

}