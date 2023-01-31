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
    auto button = std::make_unique<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MenuState&){});
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(sf::Vector2i{3, 3}));
    EXPECT_CALL(*button, update(Eq(sf::Vector2i{3, 3})));

    sut = std::make_unique<UserInterface>();
    sut->addButton(std::move(button), mockCallback);
    sut->update(window);
}

TEST_F(UserInterfaceTest, uiWillGetEmptyActionIfNoButtonsWerePressed)
{
    auto button = std::make_unique<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MenuState&){});
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(false));

    sut = std::make_unique<UserInterface>();
    sut->addButton(std::move(button), mockCallback);
    EXPECT_EQ(sut->getActiveAction(), std::nullopt);
}

// TEST_F(UserInterfaceTest, uiWillUpdateAddedDropDownListWithMousePositionOnWindow)
// {
//     auto button = std::make_unique<NiceMock<ButtonMock>>();
//     auto dropDownList = std::make_shared<NiceMock<DropDownListMock>>();
//     EXPECT_CALL(window, getMousePosition()).WillOnce(Return(sf::Vector2i{3, 3}));
//     EXPECT_CALL(*dropDownList, update(Eq(sf::Vector2i{3, 3})));

//     sut = std::make_unique<UserInterface>();
//     sut->addDropDownList("TestDropDownList", button);
//     sut->update(window);
// }
/*
dropDownList(std::string, std::unique_ptr<IButton>)

dropDownList->addSection(std::string);

*/

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
        toGameButton = std::make_unique<NiceMock<ButtonMock>>();
        toSettingsButton = std::make_unique<NiceMock<ButtonMock>>();
        toEditorButton = std::make_unique<NiceMock<ButtonMock>>();
        toExitButton = std::make_unique<NiceMock<ButtonMock>>();
    }
    std::unique_ptr<NiceMock<ButtonMock>> toGameButton;
    std::unique_ptr<NiceMock<ButtonMock>> toSettingsButton;
    std::unique_ptr<NiceMock<ButtonMock>> toEditorButton;
    std::unique_ptr<NiceMock<ButtonMock>> toExitButton;
    NiceMock<Core::WindowMock> window;

    void setupMainMenuButtons()
    {
        EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(ByMove(std::move(toGameButton))))
            .WillOnce(Return(ByMove(std::move(toSettingsButton))))
            .WillOnce(Return(ByMove(std::move(toEditorButton))))
            .WillOnce(Return(ByMove(std::move(toExitButton))));
    }
};

TEST_F(MainMenuGuiManagerTest, uiWillUpdateFourButtonsCreatedByMainMenuGuiManager)
{
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, getMousePosition()).Times(4).WillRepeatedly(Return(sf::Vector2i{3, 3}));
    sut->update(window);
}

TEST_F(MainMenuGuiManagerTest, uiWillDrawFourButtonsCreatedByMainMenuGuiManager)
{
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(8);
    sut->drawTo(window);
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToGameButtonHasBeenPressed)
{
    EXPECT_CALL(*toGameButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToSettingsButtonHasBeenPressed)
{
    EXPECT_CALL(*toSettingsButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToEditorButtonHasBeenPressed)
{
    EXPECT_CALL(*toEditorButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToExitButtonHasBeenPressed)
{
    EXPECT_CALL(*toExitButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

struct SettingsGuiManagerTest : public GuiManagerFixture
{
    SettingsGuiManagerTest()
    {
        applyButton = std::make_unique<NiceMock<ButtonMock>>();
        backButton = std::make_unique<NiceMock<ButtonMock>>();
    }

    std::unique_ptr<NiceMock<ButtonMock>> applyButton;
    std::unique_ptr<NiceMock<ButtonMock>> backButton;
    void setupSettingsButtons()
    {
        EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(ByMove(std::move(applyButton))))
            .WillOnce(Return(ByMove(std::move(backButton))));
    }
};

TEST_F(SettingsGuiManagerTest, uiWillUpdateTwoButtonsCreatedBySettingsGuiManager)
{
    setupSettingsButtons();
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, getMousePosition()).Times(2).WillRepeatedly(Return(sf::Vector2i{3, 3}));
    sut->update(window);
}

TEST_F(SettingsGuiManagerTest, uiWillDrawTwoButtonsCreatedBySettingsGuiManager)
{
    setupSettingsButtons();
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(4);
    sut->drawTo(window);
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterApplyButtonHasBeenPressed)
{
    EXPECT_CALL(*applyButton, isPressed()).WillOnce(Return(true));
    setupSettingsButtons();
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterBackButtonHasBeenPressed)
{
    EXPECT_CALL(*backButton, isPressed()).WillOnce(Return(true));
    setupSettingsButtons();
    auto guiManager = std::make_unique<SettingsGuiManager>(std::move(buttonBuilder));
    sut = guiManager->createGui(std::make_shared<sf::Font>());
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

}