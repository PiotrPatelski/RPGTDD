#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GameLoop.h>
#include "GameMock.h"
#include "IniParserMock.h"

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
    NiceMock<IniParserMock> iniParser;
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
    EXPECT_CALL(game, updateClock());
    EXPECT_CALL(game, isWindowOpen()).WillOnce(Return(false));
    EXPECT_CALL(game, updateClock()).Times(0);
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
    EXPECT_CALL(game, startStateMachine());
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

TEST_F(GameLoopTest, gameOpensWindowWhenLoopIsRun)
{
    EXPECT_CALL(game, openWindow());
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

TEST_F(GameLoopTest, gameAppliesGraphicsSettingsWhenLoopIsRun)
{
    EXPECT_CALL(game, fetchGraphicsSettings(_));
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

TEST_F(GameLoopTest, gameAppliesPlayerInputSettingsWhenLoopIsRun)
{
    EXPECT_CALL(game, fetchPlayerInputSettings(_));
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

}