#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.h>
#include "ClockMock.h"
#include "EngineMock.h"
#include "IniParserMock.h"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::A;

struct GameTest : public testing::Test
{
    GameTest()
    {}
    std::unique_ptr<NiceMock<EngineMock>> engine = std::make_unique<NiceMock<EngineMock>>();
    GraphicsConfig dummyGraphicsConfig;
    KeyboardConfig dummyKeyboardConfig;
    NiceMock<IniParserMock> iniParser;
    std::unique_ptr<IGame> sut;
};

TEST_F(GameTest, engineChecksIfWindowIsActive)
{
    EXPECT_CALL(*engine, isWindowOpen()).WillOnce(Return(true));
    sut = std::make_unique<Game>(std::move(engine));
    bool result = sut->isWindowOpen();
    ASSERT_TRUE(result);
}

TEST_F(GameTest, engineChecksIfWindowIsNotActive)
{
    EXPECT_CALL(*engine, isWindowOpen()).WillOnce(Return(false));
    sut = std::make_unique<Game>(std::move(engine));
    bool result = sut->isWindowOpen();
    ASSERT_FALSE(result);
}

TEST_F(GameTest, engineLaunchesWindowWhenCalledByGame)
{
    EXPECT_CALL(*engine, launchWindow());
    sut = std::make_unique<Game>(std::move(engine));
    sut->openWindow();
}

TEST_F(GameTest, engineActivatesStateMachineWhenGameItsRun)
{
    EXPECT_CALL(*engine, runInitialState(testing::_));
    sut = std::make_unique<Game>(std::move(engine));
    sut->startStateMachine();
}

TEST_F(GameTest, engineDisplaysRenderedFrame)
{
    EXPECT_CALL(*engine, displayRenderedFrame());
    sut = std::make_unique<Game>(std::move(engine));
    sut->render();
}

TEST_F(GameTest, clockUpdatesDeltaTime)
{
    EXPECT_CALL(*engine, updateDeltaTime());
    sut = std::make_unique<Game>(std::move(engine));
    sut->updateClock();
}

TEST_F(GameTest, engineShouldNotCloseWindowWhenUpdateIsSuccessful)
{
    EXPECT_CALL(*engine, updateState()).WillOnce(Return(true));
    EXPECT_CALL(*engine, closeWindow()).Times(0);
    sut = std::make_unique<Game>(std::move(engine));
    sut->update();
}

TEST_F(GameTest, engineShouldCloseWindowWhenUpdateIsSuccessful)
{
    EXPECT_CALL(*engine, updateState()).WillOnce(Return(false));
    EXPECT_CALL(*engine, closeWindow());
    sut = std::make_unique<Game>(std::move(engine));
    sut->update();
}

TEST_F(GameTest, setsBuildPathString)
{
    sut = std::make_unique<Game>(std::move(engine));
    sut->setBuildPath("TEST");
    ASSERT_EQ(sut->getBuildPath(), "TEST");
}

TEST_F(GameTest, graphicsConfigShouldFetchDataFromFileWhenGameAppliesIt)
{
    ON_CALL(*engine, getGraphicsConfig).WillByDefault(ReturnRef(dummyGraphicsConfig));
    EXPECT_CALL(iniParser, parseFileTo(A<GraphicsConfig&>()));
    sut = std::make_unique<Game>(std::move(engine));
    sut->fetchGraphicsSettings(iniParser);
}

TEST_F(GameTest, playerInputConfigShouldFetchDataFromFileWhenGameAppliesIt)
{
    ON_CALL(*engine, getKeyboardConfig).WillByDefault(ReturnRef(dummyKeyboardConfig));
    EXPECT_CALL(iniParser, parseFileTo(A<KeyboardConfig&>()));
    sut = std::make_unique<Game>(std::move(engine));
    sut->fetchPlayerInputSettings(iniParser);
}

}