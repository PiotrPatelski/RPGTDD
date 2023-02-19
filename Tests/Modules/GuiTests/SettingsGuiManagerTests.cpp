#include <gtest/gtest.h>
#include <gmock/gmock.h>
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
#include <SettingsGuiManager.hpp>

namespace Gui
{

using namespace ::testing;

struct SettingsGuiManagerTest : public GuiManagerFixture
{
    SettingsGuiManagerTest()
    {
        applyButton = std::make_unique<NiceMock<ButtonMock>>();
        backButton = std::make_unique<NiceMock<ButtonMock>>();
        resolutionList = std::make_unique<NiceMock<ButtonListMock>>();
        ON_CALL(*applyButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
        ON_CALL(*backButton, getTextContent()).WillByDefault(Return(sf::Text("", sf::Font{})));
        ON_CALL(*applyButton, getBackground()).WillByDefault(Return(dummyBackground));
        ON_CALL(*backButton, getBackground()).WillByDefault(Return(dummyBackground));
    }

    std::unique_ptr<NiceMock<ButtonMock>> applyButton;
    std::unique_ptr<NiceMock<ButtonMock>> backButton;
    std::unique_ptr<NiceMock<ButtonMock>> dropDownListButton;
    std::unique_ptr<NiceMock<ButtonListMock>> resolutionList;
    void setupSettingsButtons()
    {
        EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(ByMove(std::move(applyButton))))
            .WillOnce(Return(ByMove(std::move(backButton))))
            .WillOnce(Return(ByMove(std::move(dropDownListButton))));
    }
    void setupButtonList()
    {
        EXPECT_CALL(*dropDownListBuilder, build())
            .WillOnce(Return(ByMove(std::move(resolutionList))));
    }
};

TEST_F(SettingsGuiManagerTest, uiWillDrawTwoButtonsCreatedBySettingsGuiManager)
{
    setupSettingsButtons();
    setupButtonList();
    auto guiManager = std::make_unique<SettingsGuiManager>(
        resolution,
        std::move(buttonBuilder),
        std::move(dropDownListBuilder));
    sut = guiManager->createGui(sf::Font{});
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(4);
    sut->drawTo(window);
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterApplyButtonHasBeenPressed)
{
    EXPECT_CALL(*applyButton, isPressed()).WillOnce(Return(true));
    setupSettingsButtons();
    setupButtonList();
    auto guiManager = std::make_unique<SettingsGuiManager>(
        resolution,
        std::move(buttonBuilder),
        std::move(dropDownListBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(SettingsGuiManagerTest, uiWillNotThrowWhenGettingActionAfterBackButtonHasBeenPressed)
{
    EXPECT_CALL(*backButton, isPressed()).WillOnce(Return(true));
    setupSettingsButtons();
    setupButtonList();
    auto guiManager = std::make_unique<SettingsGuiManager>(
        resolution,
        std::move(buttonBuilder),
        std::move(dropDownListBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

TEST_F(SettingsGuiManagerTest, uiWillReturnValidActionWhenButtonListHasOneAvailable)
{
    EXPECT_CALL(*resolutionList, getActiveAction()).WillOnce(Return([](States::MenuState&){}));
    setupSettingsButtons();
    setupButtonList();
    auto guiManager = std::make_unique<SettingsGuiManager>(
        resolution,
        std::move(buttonBuilder),
        std::move(dropDownListBuilder));
    sut = guiManager->createGui(sf::Font{});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    ASSERT_NO_THROW(std::get<Events::MenuAction>(result.value()));
}

}