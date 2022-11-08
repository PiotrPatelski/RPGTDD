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
    std::unique_ptr<IStateMachine> sut = std::make_unique<StateMachine>();
};

TEST_F(StateMachineTest, stateMachineHasFinishedItsWorkWhenNoStatesAreToHandle)
{
    ASSERT_TRUE(sut->isNoStateActive());
}

TEST_F(StateMachineTest, currentStateIsNotUpdatedWhenWindowIsNotOnFocus)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    EXPECT_CALL(*activeState, update(_)).Times(0);
    sut->runState(std::move(activeState));
    sut->update(false, 0.f);
}

TEST_F(StateMachineTest, currentStateIsUpdatedWhenStateMachineUpdates)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    EXPECT_CALL(*activeState, update(_));
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineChecksIfActiveStateIsDoneWhenUpdated)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    EXPECT_CALL(*activeState, isDone());
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineReadsNextStateWhenCurrentStateIsDone)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    auto nextState = std::make_unique<NiceMock<States::StateMock>>();
    ON_CALL(*activeState, isDone()).WillByDefault(Return(true));
    EXPECT_CALL(*activeState, getNextState()).WillOnce(Return(ByMove(std::move(nextState))));
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineDoesNotReadNextStateWhenCurrentStateIsNotDone)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    auto nextState = std::make_unique<NiceMock<States::StateMock>>();
    ON_CALL(*activeState, isDone()).WillByDefault(Return(false));
    EXPECT_CALL(*activeState, getNextState()).Times(0);
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

}