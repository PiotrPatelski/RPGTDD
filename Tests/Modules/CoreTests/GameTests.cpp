#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>
#include <GameLoop.h>
#include "GameMock.h"
#include "WindowMock.h"
#include "ClockMock.h"
#include "StateMachineMock.h"
#include "StateMock.h"
#include "EngineContextMock.h"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::ReturnRef;

struct GameLoopTest : public testing::Test
{
    NiceMock<GameMock> game;
    std::unique_ptr<IGameLoop> sut = std::make_unique<GameLoop>(game);
};

TEST_F(GameLoopTest, gameIsUpdatingWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(true));
    EXPECT_CALL(game, update());
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(false));
    EXPECT_CALL(game, update()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameUpdatesDeltaTimeWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(true));
    EXPECT_CALL(game, updateDeltaTime());
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(false));
    EXPECT_CALL(game, updateDeltaTime()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameCallsRenderWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(true));
    EXPECT_CALL(game, render());
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(false));
    EXPECT_CALL(game, render()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameStartsStateMachineWhenLoopIsRun)
{
    InSequence seq;
    EXPECT_CALL(game, startStateMachine()).Times(1);
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

TEST_F(GameLoopTest, gameOpensWindowWhenLoopIsRun)
{
    InSequence seq;
    EXPECT_CALL(game, openWindow()).Times(1);
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

struct GameTest : public testing::Test
{
    virtual void SetUp()
    {
        ON_CALL(engineContext, getWindow).WillByDefault(ReturnRef(window));
        ON_CALL(engineContext, getClock).WillByDefault(ReturnRef(clock));
        ON_CALL(engineContext, getStateMachine).WillByDefault(ReturnRef(stateMachine));
        sut = std::make_unique<Game>(engineContext);
    }
    NiceMock<EngineContextMock> engineContext;
    NiceMock<WindowMock> window;
    NiceMock<ClockMock> clock;
    NiceMock<StateMachineMock> stateMachine;
    std::unique_ptr<IGame> sut;
};

TEST_F(GameTest, gameChecksIfWindowIsActive)
{
    EXPECT_CALL(window, isActive()).WillOnce(Return(true));
    bool result = sut->isWindowOpen();
    ASSERT_TRUE(result);
}

TEST_F(GameTest, gameChecksIfWindowIsNotActive)
{
    EXPECT_CALL(window, isActive()).WillOnce(Return(false));
    bool result = sut->isWindowOpen();
    ASSERT_FALSE(result);
}

TEST_F(GameTest, gameActivatesStateMachineWhenItsRun)
{
    EXPECT_CALL(stateMachine, runState(_));
    sut->startStateMachine();
}

TEST_F(GameTest, WindowClearsWindow)
{
    EXPECT_CALL(window, clear());
    sut->render();
}

TEST_F(GameTest, WindowDisplaysWindow)
{
    EXPECT_CALL(window, displayWindow());
    sut->render();
}

TEST_F(GameTest, ClockUpdatesDeltaTime)
{
    EXPECT_CALL(clock, updateDeltaTime());
    sut->updateDeltaTime();
}

TEST_F(GameTest, GameShouldProcessSfmlEventsWhenIsUpdated)
{
    EXPECT_CALL(window, handleSfmlEvents(_));
    sut->update();
}

TEST_F(GameTest, GameShouldUpdateStateMachineUponUpdateCall)
{
    EXPECT_CALL(stateMachine, update(_, _));
    sut->update();
}

TEST_F(GameTest, GameShouldCloseWindowWhenStateMachineIsDone)
{
    EXPECT_CALL(stateMachine, isWorkDone()).WillOnce(Return(true));
    EXPECT_CALL(stateMachine, update(_, _)).Times(0);
    EXPECT_CALL(window, close());
    sut->update();
}

TEST_F(GameTest, GameShouldNotCloseWindowWhenStateMachineIsNotDone)
{
    EXPECT_CALL(stateMachine, isWorkDone()).WillOnce(Return(false));
    EXPECT_CALL(stateMachine, update(_, _));
    EXPECT_CALL(window, close()).Times(0);
    sut->update();
}

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

struct WindowTest : public testing::Test
{    
    std::unique_ptr<IWindow> sut = std::make_unique<Window>();
};

TEST_F(WindowTest, windowIsNotActiveUponCreation)
{
    ASSERT_FALSE(sut->isActive());
}

TEST_F(WindowTest, windowIsActiveWhenLaunched)
{
    sut->open();
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowRemainsActiveWhenNoClosingEventAppearedDuringUpdate)
{
    sut->open();
    sf::Event event;
    sut->handleSfmlEvents(event);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowIsNotActiveWhenClosed)
{
    sut->open();
    sut->close();
    ASSERT_FALSE(sut->isActive());
}

TEST_F(WindowTest, closingWindowThrowsWhenWindowIsNotOpen)
{
    ASSERT_THROW(sut->close(), std::runtime_error);
}

TEST_F(WindowTest, handlingSfmlEventsThrowsWhenWindowIsNotOpen)
{
    ASSERT_THROW(sut->handleSfmlEvents(sf::Event{}), std::runtime_error);
}

struct StateMachineTest : public testing::Test
{
    std::unique_ptr<IStateMachine> sut = std::make_unique<StateMachine>();
};

TEST_F(StateMachineTest, stateMachineHasFinishedItsWorkWhenNoStatesAreToHandle)
{
    ASSERT_TRUE(sut->isWorkDone());
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