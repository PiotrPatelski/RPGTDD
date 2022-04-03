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

struct GameLoopTest : public testing::Test
{
    NiceMock<GameMock> game;
    std::unique_ptr<IGameLoop> sut = std::make_unique<GameLoop>(game);
};

TEST_F(GameLoopTest, gameIsNotUpdatedWhenItIsNotRunning)
{
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(false));
    EXPECT_CALL(game, update()).Times(0);
    sut->run();
}

TEST_F(GameLoopTest, gameIsUpdatingWhenItIsRunning)
{
    EXPECT_CALL(game, getIsRunning()).WillOnce(Return(true));
    EXPECT_CALL(game, update());
    sut->run();
}

}