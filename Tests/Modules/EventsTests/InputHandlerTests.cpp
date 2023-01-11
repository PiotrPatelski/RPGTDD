#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputHandler.hpp>
#include <GameState.hpp>
#include <MainMenuState.hpp>
#include <SettingsState.hpp>
#include <EditorState.hpp>
#include <ConfigManagerMock.hpp>
#include <ButtonMock.hpp>
#include <StateMock.h>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Events
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;
using ::testing::MockFunction;
using ::testing::_;
using ::testing::A;

struct MainMenuInputHandlerTest : public testing::Test
{
    MainMenuInputHandlerTest()
    {
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        configManager = std::make_shared<Core::ConfigManager>();
    }

    std::shared_ptr<Core::IConfigManager> configManager;
    std::unique_ptr<NiceMock<States::StateMock>> state = std::make_unique<NiceMock<States::StateMock>>();
    std::unique_ptr<NiceMock<Gui::ButtonMock>> button = std::make_unique<NiceMock<Gui::ButtonMock>>();
};

TEST_F(MainMenuInputHandlerTest, handlerWillReturnNullptrButIsNotReadyToChangeStateWhenButtonIsNotPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(false));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToGameState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_FALSE(sut->isStateReadyToChange());
    ASSERT_EQ(nextState, nullptr);
}

TEST_F(MainMenuInputHandlerTest, handlerWillReturnValidGameStateAndIsReadyToChangeToItWhenButtonIsPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(true));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToGameState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_TRUE(sut->isStateReadyToChange());
    ASSERT_EQ(typeid(*nextState), typeid(States::GameState));
}

TEST_F(MainMenuInputHandlerTest, handlerWillReturnValidMainMenuStateAndIsReadyToChangeToItWhenButtonIsPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(true));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToMainMenuState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_TRUE(sut->isStateReadyToChange());
    ASSERT_EQ(typeid(*nextState), typeid(States::MainMenuState));
}

TEST_F(MainMenuInputHandlerTest, handlerWillReturnValidEditorStateAndIsReadyToChangeToItWhenButtonIsPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(true));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToEditorState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_TRUE(sut->isStateReadyToChange());
    ASSERT_EQ(typeid(*nextState), typeid(States::EditorState));
}

TEST_F(MainMenuInputHandlerTest, handlerWillReturnValidSettingsStateAndIsReadyToChangeToItWhenButtonIsPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(true));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToSettingsState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_TRUE(sut->isStateReadyToChange());
    ASSERT_EQ(typeid(*nextState), typeid(States::SettingsState));
}

TEST_F(MainMenuInputHandlerTest, handlerWillReturnValidExitStateAndIsReadyToToExitWhenButtonIsPressed)
{
    auto sut = std::make_unique<MainMenuInputHandler>(configManager);
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(true));

    Gui::StateChangingButton actionButton{std::move(button), Events::ToExitState()};
    auto nextState = sut->getNextStateOnActiveButton(actionButton);
    ASSERT_TRUE(sut->isStateReadyToChange());
    ASSERT_EQ(nextState, nullptr);
}

}