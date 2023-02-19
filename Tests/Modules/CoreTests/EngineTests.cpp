#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Engine.hpp>
#include <IniParser.hpp>
#include "WindowMock.hpp"
#include "ClockMock.hpp"
#include "StateMachineMock.hpp"
#include "EngineMock.hpp"
#include "CoreBuilderMock.hpp"
#include "AssetsManagerMock.hpp"
#include "StateMock.hpp"


#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Core
{

using namespace ::testing;

struct EngineTest : public testing::Test
{
    EngineTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        configManager = std::make_shared<ConfigManager>();
        window = std::make_unique<NiceMock<::Types::WindowMock>>();
        clock = std::make_unique<NiceMock<ClockMock>>();
        stateMachine = std::make_unique<NiceMock<StateMachineMock>>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>();
    }
    std::shared_ptr<ConfigManager> configManager;
    std::unique_ptr<NiceMock<::Types::WindowMock>> window;
    std::unique_ptr<NiceMock<ClockMock>> clock;
    std::unique_ptr<NiceMock<StateMachineMock>> stateMachine;
    std::unique_ptr<NiceMock<FileMgmt::AssetsManagerMock>> assetsManager;
    NiceMock<CoreBuilderMock> coreBuilder;
    std::unique_ptr<IEngine> sut;
};

TEST_F(EngineTest, engineWindowIsNotOpenWhenIsActiveIsFalse)
{
    EXPECT_CALL(*window, isActive()).WillOnce(Return(false));

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_FALSE(sut->isWindowOpen());
}

TEST_F(EngineTest, engineWindowIsOpenWhenIsActiveIsTrue)
{
    EXPECT_CALL(*window, isActive()).WillOnce(Return(true));

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_TRUE(sut->isWindowOpen());
}

TEST_F(EngineTest, windowIsOpenWhenEngineLaunchesIt)
{
    EXPECT_CALL(*window, openWithSettings(A<const FileMgmt::GraphicsConfig&>()));

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->launchWindow(configManager->getGraphics());
}

TEST_F(EngineTest, windowClosesWhenEngineCallsIt)
{
    EXPECT_CALL(*window, close());

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->closeWindow();
}

TEST_F(EngineTest, stateWillNotBeUpdatedIfEngineDidntRunInitialState)
{
    EXPECT_CALL(*window, handleSfmlEvents(_));
    EXPECT_CALL(*stateMachine, isAnyStateActive()).WillOnce(Return(false));
    EXPECT_CALL(*window, isCurrentlyFocused()).Times(0);
    EXPECT_CALL(*window, getMousePosition()).Times(0);
    EXPECT_CALL(*clock, getDeltaTime()).Times(0);  
    EXPECT_CALL(*stateMachine, update(_,_)).Times(0);

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_FALSE(sut->updateState());
}

TEST_F(EngineTest, stateIsNotUpdatedIfWindowIsNotFocused)
{
    EXPECT_CALL(*window, handleSfmlEvents(_));
    EXPECT_CALL(*stateMachine, isAnyStateActive()).WillOnce(Return(true));
    EXPECT_CALL(*window, isCurrentlyFocused()).WillOnce(Return(false));
    EXPECT_CALL(*window, getMousePosition()).Times(0);
    EXPECT_CALL(*clock, getDeltaTime()).Times(0);
    EXPECT_CALL(*stateMachine, update(_,_)).Times(0);

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_TRUE(sut->updateState());
}

TEST_F(EngineTest, stateIsUpdatedIfEngineRunInitialState)
{
    EXPECT_CALL(*window, handleSfmlEvents(_));
    EXPECT_CALL(*stateMachine, isAnyStateActive()).WillOnce(Return(true));
    EXPECT_CALL(*window, isCurrentlyFocused()).WillOnce(Return(true));
    EXPECT_CALL(*clock, getDeltaTime());
    EXPECT_CALL(*stateMachine, update(_,_));

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createClock()).WillByDefault(Return(ByMove(std::move(clock))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_TRUE(sut->updateState());
}

TEST_F(EngineTest, windowClearsAndDisplaysButDoesNotDrawStateOutputWhenDisplayRenderedFrameWithNoStateActive)
{
    std::shared_ptr<NiceMock<States::StateMock>> activeState = std::make_shared<NiceMock<States::StateMock>>();
    EXPECT_CALL(*window, clear());
    EXPECT_CALL(*stateMachine, isAnyStateActive()).WillOnce(Return(false));
    EXPECT_CALL(*stateMachine, getCurrentState()).Times(0);
    EXPECT_CALL(*activeState, drawOutput(_)).Times(0);
    EXPECT_CALL(*window, display());

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->displayRenderedFrame();
}

TEST_F(EngineTest, windowClearsDrawsStateOutputAndDisplaysWhenDisplayRenderedFrameWithActiveState)
{
    std::shared_ptr<NiceMock<States::StateMock>> activeState = std::make_shared<NiceMock<States::StateMock>>();
    EXPECT_CALL(*window, clear());
    EXPECT_CALL(*stateMachine, isAnyStateActive()).WillOnce(Return(true));
    EXPECT_CALL(*stateMachine, getCurrentState()).WillOnce(Return(activeState));
    EXPECT_CALL(*activeState, drawOutput(A<::Types::IWindow&>()));
    EXPECT_CALL(*window, display());

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->displayRenderedFrame();
}

TEST_F(EngineTest, engineForwardsUpdateDeltaTimeToClock)
{
    EXPECT_CALL(*clock, updateDeltaTime());

    ON_CALL(coreBuilder, createClock()).WillByDefault(Return(ByMove(std::move(clock))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->updateDeltaTime();
}

TEST_F(EngineTest, engineForwardsInitialStateToRunOnStateMachine)
{
    EXPECT_CALL(*stateMachine, setState(A<std::shared_ptr<States::IState>>()));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));

    sut = std::make_unique<Engine>(coreBuilder);
    sut->runInitialState(configManager);
}

}