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

namespace Gui
{

using namespace ::testing;

struct MenuGuiTest : public testing::Test
{
    std::unique_ptr<UserInterface> sut;
    NiceMock<Core::WindowMock> window;
};

TEST_F(MenuGuiTest, uiWillUpdateAddedButtonWithMousePositionOnWindow)
{
    auto button = std::make_unique<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MenuState&){});
    auto mousePosition = sf::Vector2i{3, 3};
    EXPECT_CALL(*button, update(Eq(mousePosition)));

    sut = std::make_unique<MenuGui>();
    sut->addButton(std::move(button), mockCallback);
    sut->update(mousePosition);
}

TEST_F(MenuGuiTest, uiWillGetEmptyActionIfNoButtonsWerePressed)
{
    auto button = std::make_unique<NiceMock<ButtonMock>>();
    auto mockCallback = Events::StateAction([](States::MenuState&){});
    EXPECT_CALL(*button, isPressed()).WillOnce(Return(false));

    sut = std::make_unique<MenuGui>();
    sut->addButton(std::move(button), mockCallback);
    EXPECT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(MenuGuiTest, uiWillDrawAddedButtonListToPassedWindow)
{
    auto dropDownList = std::make_unique<NiceMock<ButtonListMock>>();
    EXPECT_CALL(*dropDownList, drawTo(A<Core::IWindow&>()));

    sut = std::make_unique<MenuGui>();
    sut->addButtonList(std::move(dropDownList));
    sut->drawTo(window);
}

TEST_F(MenuGuiTest, uiWillUpdateAddedButtonListWithMousePositionOnWindow)
{
    auto dropDownList = std::make_unique<NiceMock<ButtonListMock>>();
    auto mousePosition = sf::Vector2i{3, 3};
    EXPECT_CALL(*dropDownList, update(Eq(mousePosition)));

    sut = std::make_unique<MenuGui>();
    sut->addButtonList(std::move(dropDownList));
    sut->update(mousePosition);
}

}