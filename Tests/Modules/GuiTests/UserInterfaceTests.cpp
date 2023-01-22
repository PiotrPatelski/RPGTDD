#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.hpp>
#include <GuiManager.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>
#include <ButtonBuilderMock.hpp>
#include <StateMock.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Gui
{

using namespace ::testing;

struct UserInterfaceTest : public testing::Test
{
    std::unique_ptr<IUserInterface> sut;
    NiceMock<Core::WindowMock> window;
};

TEST_F(UserInterfaceTest, uiWillUpdateAddedButtonWithMousePositionOnWindow)
{
    auto button = std::make_shared<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MainMenuState&){});
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(sf::Vector2i{3, 3}));
    EXPECT_CALL(*button, update(Eq(sf::Vector2i{3, 3})));

    sut = std::make_unique<UserInterface>();
    sut->addButton(std::move(button), mockCallback);
    sut->update(window);
}

TEST_F(UserInterfaceTest, uiWillGetEmptyActionIfNoButtonsWerePressed)
{
    auto button = std::make_shared<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MainMenuState&){});
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(false));

    sut = std::make_unique<UserInterface>();
    sut->addButton(std::move(button), mockCallback);
    EXPECT_EQ(sut->getActiveAction(), std::nullopt);
}

struct GuiManagerFixture : public UserInterfaceTest
{
    GuiManagerFixture()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
        ON_CALL(*buttonBuilder, withTextContent(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withFont(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, atPosition(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withSize(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
    }
    std::unique_ptr<NiceMock<ButtonBuilderMock>> buttonBuilder;
};

struct MainMenuGuiManagerTest : public GuiManagerFixture
{
    MainMenuGuiManagerTest()
    {
        toGameButton = std::make_shared<NiceMock<ButtonMock>>();
        toSettingsButton = std::make_shared<NiceMock<ButtonMock>>();
        toEditorButton = std::make_shared<NiceMock<ButtonMock>>();
        toExitButton = std::make_shared<NiceMock<ButtonMock>>();
        EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(toGameButton))
            .WillOnce(Return(toSettingsButton))
            .WillOnce(Return(toEditorButton))
            .WillOnce(Return(toExitButton));
    }
    std::shared_ptr<NiceMock<ButtonMock>> toGameButton;
    std::shared_ptr<NiceMock<ButtonMock>> toSettingsButton;
    std::shared_ptr<NiceMock<ButtonMock>> toEditorButton;
    std::shared_ptr<NiceMock<ButtonMock>> toExitButton;
    NiceMock<Core::WindowMock> window;
};

TEST_F(MainMenuGuiManagerTest, uiWillUpdateFourButtonsCreatedByMainMenuGuiManager)
{
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, getMousePosition()).Times(4).WillRepeatedly(Return(sf::Vector2i{3, 3}));
    sut->update(window);
}

TEST_F(MainMenuGuiManagerTest, uiWillDrawFourButtonsCreatedByMainMenuGuiManager)
{
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(8);
    sut->drawTo(window);
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToGameButtonHasBeenPressed)
{
    EXPECT_CALL(*toGameButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MainMenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToSettingsButtonHasBeenPressed)
{
    EXPECT_CALL(*toSettingsButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MainMenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToEditorButtonHasBeenPressed)
{
    EXPECT_CALL(*toEditorButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MainMenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToExitButtonHasBeenPressed)
{
    EXPECT_CALL(*toExitButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MainMenuAction>(result.value()));
}

struct SettingsGuiManagerTest : public GuiManagerFixture
{
    SettingsGuiManagerTest()
    {
        applyButton = std::make_shared<NiceMock<ButtonMock>>();
        backButton = std::make_shared<NiceMock<ButtonMock>>();
        EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(applyButton))
            .WillOnce(Return(backButton));
    }

    std::shared_ptr<NiceMock<ButtonMock>> applyButton;
    std::shared_ptr<NiceMock<ButtonMock>> backButton;
};

TEST_F(SettingsGuiManagerTest, uiWillUpdateTwoButtonsCreatedBySettingsGuiManager)
{
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, getMousePosition()).Times(2).WillRepeatedly(Return(sf::Vector2i{3, 3}));
    sut->update(window);
}

TEST_F(SettingsGuiManagerTest, uiWillDrawTwoButtonsCreatedBySettingsGuiManager)
{
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(4);
    sut->drawTo(window);
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterApplyButtonHasBeenPressed)
{
    EXPECT_CALL(*applyButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::SettingsAction>(result.value()));
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterBackButtonHasBeenPressed)
{
    EXPECT_CALL(*backButton, isPressed()).WillOnce(Return(true));
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::SettingsAction>(result.value()));
}

}