#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiActionMock.hpp>
#include <ButtonListMock.hpp>
#include <WindowMock.hpp>
#include <EditorGui.hpp>
#include <TileSelectorMock.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiTest : public testing::Test
{
    std::unique_ptr<EditorGui> sut;
    std::unique_ptr<NiceMock<ButtonListMock>> pauseButtons = std::make_unique<NiceMock<ButtonListMock>>();
    std::unique_ptr<NiceMock<TileSelectorMock>> tileSelector = std::make_unique<NiceMock<TileSelectorMock>>();
    const sf::Vector2i currentMousePosition{30, 30};
};


TEST_F(EditorGuiTest, EditorGuiExecutesGivenAction)
{
    NiceMock<Events::GuiActionMock> guiAction;
    EXPECT_CALL(guiAction, execute(A<EditorGui&>()));
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->acceptRequest(guiAction);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotUpdatePauseMenuWhenNotPaused)
{
    EXPECT_CALL(*pauseButtons, update(_)).Times(0);
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiUpdatesPauseMenuWhenPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    EXPECT_CALL(*pauseButtons, update(Eq(currentMousePosition)));
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->togglePause();
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiDrawsPauseMenuWhenPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    EXPECT_CALL(*pauseButtons, drawTo(A<::Types::Window&>()));
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->togglePause();
    NiceMock<::Types::WindowMock> window;
    sut->drawTo(window);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotDrawPauseMenuWhenNotPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    EXPECT_CALL(*pauseButtons, drawTo(A<::Types::Window&>())).Times(0);
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    NiceMock<::Types::WindowMock> window;
    sut->drawTo(window);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotUpdateTextureSelectorWhenPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    auto tileSelector = std::make_unique<NiceMock<TileSelectorMock>>();
    EXPECT_CALL(*pauseButtons, update(Eq(currentMousePosition)));
    EXPECT_CALL(*tileSelector, update(Eq(currentMousePosition))).Times(0);
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->togglePause();
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotUpdateTileSelectorWhenIsNotToggledAndIsNotPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    auto tileSelector = std::make_unique<NiceMock<TileSelectorMock>>();
    EXPECT_CALL(*pauseButtons, update(Eq(currentMousePosition))).Times(0);
    EXPECT_CALL(*tileSelector, update(Eq(currentMousePosition))).Times(0);
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiUpdatesTileSelectorWhenIsToggledAndIsNotPaused)
{
    auto pauseButtons = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    auto tileSelector = std::make_unique<NiceMock<TileSelectorMock>>();
    EXPECT_CALL(*pauseButtons, update(Eq(currentMousePosition))).Times(0);
    EXPECT_CALL(*tileSelector, update(Eq(currentMousePosition)));
    sut = std::make_unique<EditorGui>(PauseMenu{std::move(pauseButtons), ::Types::Background{}}, std::move(tileSelector));
    sut->toggleTileSelector();
    sut->update(currentMousePosition);
}

}