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
    std::unique_ptr<NiceMock<States::StateMock>> activeState = std::make_unique<NiceMock<States::StateMock>>();
    std::unique_ptr<NiceMock<States::StateMock>> nextState = std::make_unique<NiceMock<States::StateMock>>();
    std::unique_ptr<IStateMachine> sut = std::make_unique<StateMachine>();
};

TEST_F(StateMachineTest, stateMachineHasFinishedItsWorkWhenNoStatesAreToHandle)
{
    ASSERT_TRUE(sut->isNoStateActive());
}

TEST_F(StateMachineTest, stateMachineHasNotFinishedItsWorkWhenStateIsActive)
{
    sut->runState(std::move(activeState));
    ASSERT_FALSE(sut->isNoStateActive());
}

TEST_F(StateMachineTest, currentStateIsNotUpdatedWhenWindowIsNotOnFocus)
{
    EXPECT_CALL(*activeState, update(_)).Times(0);
    sut->runState(std::move(activeState));
    sut->update(false, 0.f);
}

TEST_F(StateMachineTest, currentStateIsUpdatedWhenStateMachineUpdates)
{
    EXPECT_CALL(*activeState, update(_));
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineChecksIfActiveStateIsDoneWhenUpdated)
{
    EXPECT_CALL(*activeState, isDone());
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineReadsNextStateWhenCurrentStateIsDone)
{

    ON_CALL(*activeState, isDone()).WillByDefault(Return(true));
    EXPECT_CALL(*activeState, getNextState()).WillOnce(Return(ByMove(std::move(nextState))));
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineDoesNotReadNextStateWhenCurrentStateIsNotDone)
{
    ON_CALL(*activeState, isDone()).WillByDefault(Return(false));
    EXPECT_CALL(*activeState, getNextState()).Times(0);
    sut->runState(std::move(activeState));
    sut->update(true, 0.f);
}

TEST_F(StateMachineTest, stateMachineGetsOutputFromState)
{
    auto background = std::make_shared<sf::RectangleShape>(sf::Vector2f(480, 480));
    const sf::Texture texture;
    background->setTexture(&texture);
    EXPECT_CALL(*activeState, generateOutput()).WillOnce(Return(States::StateOutput{background}));
    sut->runState(std::move(activeState));
    EXPECT_NE(sut->getOutput().background->getTexture(), nullptr);
}

}