#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>
#include <GameLoop.h>
#include "GameMock.h"

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
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(true));
    EXPECT_CALL(game, update());
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(false));
    EXPECT_CALL(game, update()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameUpdatesDeltaTimeWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(true));
    EXPECT_CALL(game, updateDeltaTime());
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(false));
    EXPECT_CALL(game, updateDeltaTime()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameCallsRenderWhenItIsRunning)
{
    InSequence seq;
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(true));
    EXPECT_CALL(game, render());
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(false));
    EXPECT_CALL(game, render()).Times(0);
    sut->run();
}

}