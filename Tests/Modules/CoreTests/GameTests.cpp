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
    ASSERT_FALSE(sut->getIsGameRunning());
}

TEST_F(GameLoopTest, gameIsRunningWhenItIsSetToRun)
{
    sut->run();

    ASSERT_TRUE(sut->getIsGameRunning());
}

TEST_F(GameLoopTest, gameIsUpdatingWhenItIsRunning)
{
    EXPECT_CALL(game, update());
    sut->run();
}

}