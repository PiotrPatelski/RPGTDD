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
#include "GraphicsConfigMock.h"
#include "IniParserMock.h"

#define TEST_PATH _TEST_ASSETS_PATH
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
    EXPECT_CALL(game, applyGraphicsSettings());
    ON_CALL(game, isWindowOpen()).WillByDefault(Return(false));
    sut->run();
}

struct GameTest : public testing::Test
{
    GameTest()
    {
        ON_CALL(engineContext, getWindow).WillByDefault(ReturnRef(window));
        ON_CALL(engineContext, getClock).WillByDefault(ReturnRef(clock));
        ON_CALL(engineContext, getStateMachine).WillByDefault(ReturnRef(stateMachine));
        ON_CALL(engineContext, getGraphicsConfig).WillByDefault(ReturnRef(graphicsConfig));
        sut = std::make_unique<Game>(engineContext);
    }
    NiceMock<EngineContextMock> engineContext;
    NiceMock<WindowMock> window;
    NiceMock<ClockMock> clock;
    NiceMock<StateMachineMock> stateMachine;
    NiceMock<GraphicsConfigMock> graphicsConfig;
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

TEST_F(GameTest, GraphicsConfigShouldFetchDataFromFileWhenGameAppliesGraphicsSettings)
{
    EXPECT_CALL(graphicsConfig, fetchSettingsFromFile(_));
    sut->applyGraphicsSettings();
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
    NiceMock<GraphicsConfigMock> graphicsConfig;
    WindowTest()
    {
        ON_CALL(graphicsConfig, getFullscreen).WillByDefault(Return(false));
        ON_CALL(graphicsConfig, getVerticalSync).WillByDefault(Return(false));
        ON_CALL(graphicsConfig, getFrameRateLimit).WillByDefault(Return(30));
        ON_CALL(graphicsConfig, getContextSettings).WillByDefault(Return(sf::ContextSettings{}));
        ON_CALL(graphicsConfig, getResolution).WillByDefault(Return(sf::VideoMode(480,480)));
    }
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

struct GraphicsConfigTest : public testing::Test
{
    std::unique_ptr<IGraphicsConfig> sut = std::make_unique<GraphicsConfig>();
    NiceMock<IniParserMock> iniParser;
    GraphicsData fetchedData{};
};

TEST_F(GraphicsConfigTest, graphicsConfigSuccessfullyFetchesFile)
{
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    ASSERT_NO_THROW(sut->fetchSettingsFromFile(iniParser));
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsGameWindowTitleFromFetchedFileContent)
{
    fetchedData.gameTitle = "TEST";
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_EQ(sut->getGameTitle(), "TEST");
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsResolutionFromFetchedFileContent)
{
    fetchedData.width = 480;
    fetchedData.height = 620;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_EQ(sut->getResolution().width, 480);
    ASSERT_EQ(sut->getResolution().height, 620);
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsFullscreenTrueFromFetchedFileContent)
{
    fetchedData.fullscreen = true;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_TRUE(sut->getFullscreen());
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsFullscreenFalseFromFetchedFileContent)
{
    fetchedData.fullscreen = false;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_FALSE(sut->getFullscreen());
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsFrameRateLimitFromFetchedFileContent)
{
    fetchedData.frameRateLimit = 30;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_EQ(sut->getFrameRateLimit(), 30);
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsVSyncFlagFromFetchedFileContent)
{
    fetchedData.verticalSync = true;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_TRUE(sut->getVerticalSync());
}

TEST_F(GraphicsConfigTest, graphicsConfigFillsAntialiasingLevelFromFetchedFileContent)
{
    fetchedData.antialiasingLevel = 30;
    EXPECT_CALL(iniParser, fetchDataFromGraphicsFile()).WillOnce(Return(fetchedData));
    sut->fetchSettingsFromFile(iniParser);
    ASSERT_EQ(sut->getContextSettings().antialiasingLevel, 30);
}

struct IniParserTest : public testing::Test
{
    const std::string pathToFile = TEST_PATH;
    std::unique_ptr<IIniParser> sut = std::make_unique<IniParser>(pathToFile);
};

TEST_F(IniParserTest, IniParserDoesNotThrowWhenGraphicsFileIsValid)
{
    ASSERT_NO_THROW(sut->fetchDataFromGraphicsFile());
}

}