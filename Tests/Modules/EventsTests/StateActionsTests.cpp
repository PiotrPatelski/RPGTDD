#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateActions.hpp>
#include <StateMock.hpp>
#include <ConfigManagerMock.hpp>
#include <Config.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Events
{

using namespace ::testing;

struct StateActionsTest : public testing::Test
{
    StateActionsTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        graphicsConfig.resolution = sf::VideoMode(480, 480);
    }
    std::shared_ptr<NiceMock<Core::ConfigManagerMock>> configManager;
    FileMgmt::GraphicsConfig graphicsConfig;
    FileMgmt::KeyboardConfig keyboardConfig;
};

TEST_F(StateActionsTest, toMainMenuStateActionWillFinishCurrentStateAndCreateMainMenuStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(*configManager, getGraphics()).WillRepeatedly(ReturnRef(graphicsConfig));
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToMainMenuState()(state));
}

TEST_F(StateActionsTest, toGameStateActionWillFinishCurrentStateAndCreateGameStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(*configManager, getGraphics()).WillOnce(ReturnRef(graphicsConfig));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToGameState()(state));
}

TEST_F(StateActionsTest, buttonActionWillFinishCurrentStateAndCreateSettingsStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(*configManager, getGraphics()).WillRepeatedly(ReturnRef(graphicsConfig));
    EXPECT_CALL(*configManager, getKeyboard()).WillOnce(ReturnRef(keyboardConfig));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToSettingsState()(state));
}

TEST_F(StateActionsTest, toEditorStateActionWillFinishCurrentStateAndCreateEditorStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(*configManager, getGraphics()).WillOnce(ReturnRef(graphicsConfig));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToEditorState()(state));
}

TEST_F(StateActionsTest, toExitStateActionWillFinishCurrentStateAndCreateExitStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(state, getConfig()).Times(0);
    EXPECT_CALL(state, setNextState(IsNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToExitState()(state));
}

TEST_F(StateActionsTest, applySettingsActionWillFinishCurrentStateAndCreateSettingsStateAsNextState)
{
    auto state = NiceMock<States::MenuStateMock>();
    ON_CALL(*configManager, getGraphics()).WillByDefault(ReturnRef(graphicsConfig));
    ON_CALL(*configManager, getKeyboard()).WillByDefault(ReturnRef(keyboardConfig));
    EXPECT_CALL(*configManager, applyDiff());
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ApplySettings()(state));
}

TEST_F(StateActionsTest, setResolutionToActionWillQueueConfigsRequest)
{
    auto resolution = sf::VideoMode(480, 480);
    auto state = NiceMock<States::MenuStateMock>();
    EXPECT_CALL(*configManager, queueGraphicsRequest(A<std::function<void(FileMgmt::GraphicsConfig&)>>()));
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    ASSERT_NO_THROW(Events::SetResolutionTo{resolution}(state));
}

}