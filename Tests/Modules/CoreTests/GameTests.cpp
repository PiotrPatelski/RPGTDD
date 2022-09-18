#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>
#include <GameLoop.h>
#include "GameMock.h"
#include "WindowManagerBuilderMock.h"


namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;

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
    std::unique_ptr<WindowManagerMock> windowMngr = std::make_unique<NiceMock<WindowManagerMock>>();
    std::unique_ptr<IGame> sut = std::make_unique<Game>(*windowMngr);
};

TEST_F(GameTest, gameChecksIfWindowIsActive)
{
    // EXPECT_CALL(windowMngrBuilder, build());

    EXPECT_CALL(*windowMngr, isWindowActive()).WillOnce(Return(true));
    bool result = sut->isWindowActive();
    ASSERT_TRUE(result);
}

TEST_F(GameTest, gameChecksIfWindowIsNotActive)
{
    EXPECT_CALL(*windowMngr, isWindowActive()).WillOnce(Return(false));
    bool result = sut->isWindowActive();
    ASSERT_FALSE(result);
}

}