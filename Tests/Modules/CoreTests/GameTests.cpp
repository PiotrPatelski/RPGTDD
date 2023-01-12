#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Game.hpp>
#include "ClockMock.hpp"
#include "EngineMock.hpp"
#include "IniParserMock.hpp"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::A;
using ::testing::_;

struct GameTest : public testing::Test
{
    GameTest()
    {
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
    }
    std::unique_ptr<NiceMock<EngineMock>> engine = std::make_unique<NiceMock<EngineMock>>();
    NiceMock<FileMgmt::IniParserMock> iniParser;
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
    EXPECT_CALL(*engine, launchWindow(_));
    sut = std::make_unique<Game>(std::move(engine));
    sut->openWindow();
}

TEST_F(GameTest, engineActivatesStateMachineWhenGameItsRun)
{
    EXPECT_CALL(*engine, runInitialState(_));
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

TEST_F(GameTest, gameConstructionShouldNotThrowWhenConfigFilePathsAreValid)
{
    ASSERT_NO_THROW(std::make_unique<Game>(std::move(engine)));
}

TEST_F(GameTest, gameConstructionShouldThrowWhenConfigFilePathsAreInvalid)
{
    FileMgmt::IniParser::setBuildPath("Invalid/Test/Path");
    ASSERT_THROW(std::make_unique<Game>(std::move(engine)), std::runtime_error);
}

}