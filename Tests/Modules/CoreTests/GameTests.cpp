#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Window.hpp>
#include <Game.h>
#include <GameLoop.h>
#include "GameMock.h"
#include "WindowMock.h"
#include "ClockMock.h"
#include "StateMachineMock.h"
#include "StateMock.h"
#include "EngineContextMock.h"
#include "IniParserMock.h"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"
namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::A;

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

TEST_F(GameLoopTest, gameProvidesBuildPathWhenLoopIsRun)
{
    EXPECT_CALL(game, getBuildPath());
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

struct GameTest : public testing::Test
{
    GameTest()
    {
        engine = std::make_shared<NiceMock<EngineContextMock>>();
        ON_CALL(*engine, getClock).WillByDefault(ReturnRef(clock));
        ON_CALL(*engine, getGraphicsConfig).WillByDefault(ReturnRef(dummyGraphicsConfig));
        ON_CALL(*engine, getKeyboardConfig).WillByDefault(ReturnRef(dummyKeyboardConfig));
        sut = std::make_unique<Game>(engine);
    }
    std::shared_ptr<NiceMock<EngineContextMock>> engine;
    NiceMock<WindowMock> window;
    NiceMock<ClockMock> clock;
    NiceMock<StateMachineMock> stateMachine;
    GraphicsConfig dummyGraphicsConfig;
    KeyboardConfig dummyKeyboardConfig;
    NiceMock<IniParserMock> iniParser;
    std::unique_ptr<IGame> sut;
};

TEST_F(GameTest, engineChecksIfWindowIsActive)
{
    EXPECT_CALL(*engine, isWindowOpen()).WillOnce(Return(true));
    bool result = sut->isWindowOpen();
    ASSERT_TRUE(result);
}

TEST_F(GameTest, engineChecksIfWindowIsNotActive)
{
    EXPECT_CALL(*engine, isWindowOpen()).WillOnce(Return(false));
    bool result = sut->isWindowOpen();
    ASSERT_FALSE(result);
}

TEST_F(GameTest, engineActivatesStateMachineWhenGameItsRun)
{
    EXPECT_CALL(*engine, runInitialState());
    sut->startStateMachine();
}

TEST_F(GameTest, engineDisplaysRenderedFrame)
{
    EXPECT_CALL(*engine, displayRenderedFrame());
    sut->render();
}

TEST_F(GameTest, clockUpdatesDeltaTime)
{
    EXPECT_CALL(clock, updateDeltaTime());
    sut->updateDeltaTime();
}

TEST_F(GameTest, engineShouldNotCloseWindowWhenUpdateIsSuccessful)
{
    EXPECT_CALL(*engine, updateState()).WillOnce(Return(true));
    EXPECT_CALL(*engine, closeWindow()).Times(0);
    sut->update();
}

TEST_F(GameTest, engineShouldCloseWindowWhenUpdateIsSuccessful)
{
    EXPECT_CALL(*engine, updateState()).WillOnce(Return(false));
    EXPECT_CALL(*engine, closeWindow());
    sut->update();
}

TEST_F(GameTest, setsBuildPathString)
{
    sut->setBuildPath("TEST");
    ASSERT_EQ(sut->getBuildPath(), "TEST");
}

TEST_F(GameTest, graphicsConfigShouldFetchDataFromFileWhenGameAppliesIt)
{
    EXPECT_CALL(iniParser, parseFileTo(A<GraphicsConfig&>()));
    sut->fetchGraphicsSettings(iniParser);
}

TEST_F(GameTest, playerInputConfigShouldFetchDataFromFileWhenGameAppliesIt)
{
    EXPECT_CALL(iniParser, parseFileTo(A<KeyboardConfig&>()));
    sut->fetchPlayerInputSettings(iniParser);
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
    GraphicsConfig graphicsConfig{"TEST", {21,37}, 0, 0, 0, sf::ContextSettings{}};
};

TEST_F(WindowTest, windowIsNotActiveUponCreation)
{
    ASSERT_FALSE(sut->isActive());
}

TEST_F(WindowTest, windowIsActiveWhenLaunched)
{
    sut->openWithSettings(graphicsConfig);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowRemainsActiveWhenNoClosingEventAppearedDuringUpdate)
{
    sut->openWithSettings(graphicsConfig);
    sf::Event event;
    sut->handleSfmlEvents(event);
    ASSERT_TRUE(sut->isActive());
}

TEST_F(WindowTest, windowIsNotActiveWhenClosed)
{
    sut->openWithSettings(graphicsConfig);
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

TEST_F(StateMachineTest, currentStateIsNotUpdatedWhenWindowIsNotOnFocus)
{
    auto activeState = std::make_unique<NiceMock<States::StateMock>>();
    EXPECT_CALL(*activeState, update(_)).Times(0);
    sut->runState(std::move(activeState));
    sut->update(false, 0.f);
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

struct IniParserTest : public testing::Test
{
    const std::string pathToFile = TEST_PATH;
    GraphicsConfig graphicsConfig;
    KeyboardConfig keyboardConfig;
    std::unique_ptr<IIniParser> sut = std::make_unique<IniParser>(pathToFile);
};

TEST_F(IniParserTest, iniParserFillsGraphicsConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(graphicsConfig));
    ASSERT_EQ(graphicsConfig.gameTitle, "TESTCONFIG");
    ASSERT_EQ(graphicsConfig.resolution.width, 21);
    ASSERT_EQ(graphicsConfig.resolution.height, 37);
    ASSERT_TRUE(graphicsConfig.fullscreen);
    ASSERT_EQ(graphicsConfig.frameRateLimit, 30);
    ASSERT_TRUE(graphicsConfig.verticalSync);
    ASSERT_EQ(graphicsConfig.contextSettings.antialiasingLevel, 1);
}

TEST_F(IniParserTest, iniParserFillsKeyboardConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(keyboardConfig));
    ASSERT_EQ(keyboardConfig.supportedKeys.at("Escape"), 36);
    ASSERT_EQ(keyboardConfig.supportedKeys.at("D"), 3);
    ASSERT_EQ(keyboardConfig.supportedKeys.at("PageDown"), 62);
}

struct EngineTest : public testing::Test
{
    const std::string pathToFile = TEST_PATH;
    std::unique_ptr<IIniParser> parser = std::make_unique<IniParser>(pathToFile);
    std::unique_ptr<Engine> sut = std::make_unique<Engine>();
    EngineTest()
    {
        parser->parseFileTo(sut->getKeyboardConfig());
        parser->parseFileTo(sut->getGraphicsConfig());
    }
};

TEST_F(EngineTest, windowIsNotOpenWhenEngineWontRunIt)
{
    ASSERT_FALSE(sut->isWindowOpen());
}

TEST_F(EngineTest, windowIsOpenWhenEngineLaunchesIt)
{
    sut->launchWindow();
    ASSERT_TRUE(sut->isWindowOpen());
}

TEST_F(EngineTest, windowIsNotOpenAfterEngineClosesIt)
{
    sut->launchWindow();
    sut->closeWindow();
    ASSERT_FALSE(sut->isWindowOpen());
}

TEST_F(EngineTest, stateWillNotBeUpdatedIfEngineDidntRunInitialState)
{
    sut->launchWindow();
    ASSERT_FALSE(sut->updateState());
}

TEST_F(EngineTest, stateIsUpdatedIfEngineRunInitialState)
{
    sut->launchWindow();
    sut->runInitialState();
    ASSERT_TRUE(sut->updateState());
}

}