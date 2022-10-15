#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachineMock.h>
#include <State.h>

namespace States
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;

struct StatesTest : public testing::Test
{
    NiceMock<Core::StateMachineMock> stateMachine;
    std::unique_ptr<IState> sut = std::make_unique<State>(stateMachine);
};

TEST_F(StatesTest, stateIsDoneWhenSetAsDone)
{
    sut->markAsDone();
    ASSERT_TRUE(sut->isDone());
}

TEST_F(StatesTest, stateMachineRunsNextStateWhenStateCallsForChange)
{
    EXPECT_CALL(stateMachine, runState(_));
    sut->changeState();
}

}