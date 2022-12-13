#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Engine.h>
#include <IniParser.h>
#include "WindowMock.h"
#include "ClockMock.h"
#include "StateMachineMock.h"
#include "EngineMock.h"
#include "CoreBuilderMock.h"
#include "AssetsManagerMock.h"


#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

struct EngineTest : public testing::Test
{
    std::unique_ptr<NiceMock<WindowMock>> window = std::make_unique<NiceMock<WindowMock>>();
    std::unique_ptr<NiceMock<ClockMock>> clock = std::make_unique<NiceMock<ClockMock>>();
    std::unique_ptr<NiceMock<StateMachineMock>> stateMachine = std::make_unique<NiceMock<StateMachineMock>>();
    std::unique_ptr<NiceMock<MainMenuAssetsManagerMock>> assetsManager = std::make_unique<NiceMock<MainMenuAssetsManagerMock>>();
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
    EXPECT_CALL(*window, openWithSettings(_));

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->launchWindow();
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
    EXPECT_CALL(*stateMachine, isNoStateActive()).WillOnce(Return(true));
    EXPECT_CALL(*window, isCurrentlyFocused()).Times(0);
    EXPECT_CALL(*clock, getDeltaTime()).Times(0);  
    EXPECT_CALL(*stateMachine, update(_,_)).Times(0);

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    ASSERT_FALSE(sut->updateState());
}

TEST_F(EngineTest, stateIsUpdatedIfEngineRunInitialState)
{
    EXPECT_CALL(*window, handleSfmlEvents(_));
    EXPECT_CALL(*stateMachine, isNoStateActive()).WillOnce(Return(false));
    EXPECT_CALL(*window, isCurrentlyFocused());
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
    EXPECT_CALL(*window, clear());
    EXPECT_CALL(*stateMachine, isNoStateActive()).WillOnce(Return(true));
    EXPECT_CALL(*window, drawStateOutput(_)).Times(0);
    EXPECT_CALL(*stateMachine, getOutput()).Times(0);
    EXPECT_CALL(*window, display());

    ON_CALL(coreBuilder, createWindow()).WillByDefault(Return(ByMove(std::move(window))));
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));
    sut = std::make_unique<Engine>(coreBuilder);

    sut->displayRenderedFrame();
}

TEST_F(EngineTest, windowClearsDrawsStateOutputAndDisplaysWhenDisplayRenderedFrameWithActiveState)
{
    sf::RectangleShape background(sf::Vector2f(480, 480));
    EXPECT_CALL(*window, clear());
    EXPECT_CALL(*stateMachine, isNoStateActive()).WillOnce(Return(false));
    EXPECT_CALL(*stateMachine, getOutput()).WillOnce(Return(States::StateOutput{background}));
    EXPECT_CALL(*window, drawStateOutput(_));
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
    AssetsManager::setBuildPath(TEST_PATH);
    IniParser::setBuildPath(TEST_PATH);
    EXPECT_CALL(*stateMachine, runState);
    ON_CALL(coreBuilder, createStateMachine()).WillByDefault(Return(ByMove(std::move(stateMachine))));

    sut = std::make_unique<Engine>(coreBuilder);
    IniParser{}.parseFileTo(sut->getKeyboardConfig().supportedKeys);

    sut->runInitialState();
}

TEST_F(EngineTest, engineCanGetWritableGraphicsConfig)
{
    sut = std::make_unique<Engine>(coreBuilder);

    sut->getGraphicsConfig().gameTitle = "engineCanGetGraphicsConfigAndWriteToIt";
    ASSERT_EQ(sut->getGraphicsConfig().gameTitle, "engineCanGetGraphicsConfigAndWriteToIt");
    sut->getGraphicsConfig().gameTitle = "confirmation";
    ASSERT_EQ(sut->getGraphicsConfig().gameTitle, "confirmation");
}

TEST_F(EngineTest, engineCanGetWritableKeyboardConfig)
{
    sut = std::make_unique<Engine>(coreBuilder);

    sut->getKeyboardConfig().supportedKeys.setKey("Test", 2137);
    ASSERT_EQ(sut->getKeyboardConfig().supportedKeys.getKeys().at("Test"), 2137);
    sut->getKeyboardConfig().supportedKeys.setKey("Test", 7312);
    ASSERT_EQ(sut->getKeyboardConfig().supportedKeys.getKeys().at("Test"), 7312);
}

}