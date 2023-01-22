#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonActions.hpp>
#include <StateMock.hpp>
#include <ConfigManagerMock.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Events
{

using namespace ::testing;

struct ButtonActionsTest : public testing::Test
{
    ButtonActionsTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
    }
    std::shared_ptr<NiceMock<Core::ConfigManagerMock>> configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
};

TEST_F(ButtonActionsTest, toMainMenuStateActionWillFinishCurrentStateAndCreateMainMenuStateAsNextState)
{
    auto state = NiceMock<States::SettingsStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToMainMenuState()(state));
}

TEST_F(ButtonActionsTest, toGameStateActionWillFinishCurrentStateAndCreateGameStateAsNextState)
{
    auto state = NiceMock<States::MainMenuStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToGameState()(state));
}

TEST_F(ButtonActionsTest, buttonActionWillFinishCurrentStateAndCreateSettingsStateAsNextState)
{
    auto state = NiceMock<States::MainMenuStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToSettingsState()(state));
}

TEST_F(ButtonActionsTest, toEditorStateActionWillFinishCurrentStateAndCreateEditorStateAsNextState)
{
    auto state = NiceMock<States::MainMenuStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToEditorState()(state));
}

TEST_F(ButtonActionsTest, toExitStateActionWillFinishCurrentStateAndCreateExitStateAsNextState)
{
    auto state = NiceMock<States::MainMenuStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).Times(0);
    EXPECT_CALL(state, setNextState(IsNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ToExitState()(state));
}

TEST_F(ButtonActionsTest, applySettingsActionWillFinishCurrentStateAndCreateSettingsStateAsNextState)
{
    auto state = NiceMock<States::SettingsStateMock>(configManager);
    EXPECT_CALL(state, getConfig()).WillOnce(Return(configManager));
    EXPECT_CALL(state, setNextState(NotNull()));
    EXPECT_CALL(state, finishState());
    ASSERT_NO_THROW(Events::ApplySettings()(state));
}

}