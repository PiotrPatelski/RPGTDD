#include <AssetsManager.hpp>
#include <GuiManager.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>
#include <ButtonBuilderMock.hpp>
#include <StateMock.hpp>
#include <ButtonListMock.hpp>
#include <ButtonListBuilderMock.hpp>
#include <MenuGui.hpp>
#include "GuiManagerFixture.hpp"

namespace Gui
{

using namespace ::testing;

struct MainMenuGuiManagerTest : public GuiManagerFixture
{
    MainMenuGuiManagerTest()
    {
        toGameButton = std::make_unique<NiceMock<ButtonMock>>();
        toSettingsButton = std::make_unique<NiceMock<ButtonMock>>();
        toEditorButton = std::make_unique<NiceMock<ButtonMock>>();
        toExitButton = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*toGameButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
        ON_CALL(*toSettingsButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
        ON_CALL(*toEditorButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
        ON_CALL(*toExitButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
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

TEST_F(MainMenuGuiManagerTest, uiWillDrawFourButtonsCreatedByMainMenuGuiManager)
{
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(8);
    sut->drawTo(window);
}

TEST_F(MainMenuGuiManagerTest, uiWillUpdateAllFourMainMenuButtons)
{
    auto mousePosition = sf::Vector2i{3, 3};
    EXPECT_CALL(*toGameButton, update(Eq(mousePosition)));
    EXPECT_CALL(*toSettingsButton, update(Eq(mousePosition)));
    EXPECT_CALL(*toEditorButton, update(Eq(mousePosition)));
    EXPECT_CALL(*toExitButton, update(Eq(mousePosition)));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    sut->update(mousePosition);
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToGameButtonHasBeenPressed)
{
    EXPECT_CALL(*toGameButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToSettingsButtonHasBeenPressed)
{
    EXPECT_CALL(*toSettingsButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToEditorButtonHasBeenPressed)
{
    EXPECT_CALL(*toEditorButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(MainMenuGuiManagerTest, uiWillNotThrowWhenGettingActionAfterToExitButtonHasBeenPressed)
{
    EXPECT_CALL(*toExitButton, isPressed()).WillOnce(Return(true));
    setupMainMenuButtons();
    auto guiManager = std::make_unique<MainMenuGuiManager>(
        std::move(buttonBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

}