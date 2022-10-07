#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>
#include <GameLoop.h>
#include "GameMock.h"
#include "WindowBuilderMock.h"
#include "ClockMock.h"
#include "StateMachineMock.h"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;

struct GameLoopTest : public testing::Test
{
    NiceMock<GameMock> game;
    std::unique_ptr<IGameLoop> sut = std::make_unique<GameLoop>(game);
};

TEST_F(GameLoopTest, gameIsUpdatingWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(true));
    EXPECT_CALL(game, update());
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(false));
    EXPECT_CALL(game, update()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameUpdatesDeltaTimeWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(true));
    EXPECT_CALL(game, updateDeltaTime());
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(false));
    EXPECT_CALL(game, updateDeltaTime()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameCallsRenderWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(true));
    EXPECT_CALL(game, render());
    EXPECT_CALL(game, isWindowActive()).WillOnce(Return(false));
    EXPECT_CALL(game, render()).Times(0);
    sut->run();
}

struct GameTest : public testing::Test
{
    NiceMock<WindowMock> window;
    NiceMock<ClockMock> clock;
    NiceMock<StateMachineMock> stateMachine;
    std::unique_ptr<IGame> sut = std::make_unique<Game>(window, clock, stateMachine);
};

TEST_F(GameTest, gameChecksIfWindowIsActive)
{
    EXPECT_CALL(window, isActive()).WillOnce(Return(true));
    bool result = sut->isWindowActive();
    ASSERT_TRUE(result);
}

TEST_F(GameTest, gameChecksIfWindowIsNotActive)
{
    EXPECT_CALL(window, isActive()).WillOnce(Return(false));
    bool result = sut->isWindowActive();
    ASSERT_FALSE(result);
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
    EXPECT_CALL(stateMachine, update(_, _));
    EXPECT_CALL(stateMachine, isWorkDone()).WillOnce(Return(true));
    EXPECT_CALL(window, close());
    sut->update();
}

TEST_F(GameTest, GameShouldNotCloseWindowWhenStateMachineIsNotDone)
{
    EXPECT_CALL(stateMachine, update(_, _));
    EXPECT_CALL(stateMachine, isWorkDone()).WillOnce(Return(false));
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
    std::unique_ptr<IWindow> sut = std::make_unique<Window>(sf::VideoMode(1, 1), "TestWindow");
};

TEST_F(WindowTest, windowIsActiveUponCreation)
{
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowRemainsActiveWhenNoClosingEventAppearedDuringUpdate)
{
    sf::Event event;
    sut->handleSfmlEvents(event);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowIsNotActiveWhenClosed)
{
    sut->close();
    ASSERT_FALSE(sut->isActive());
}

}