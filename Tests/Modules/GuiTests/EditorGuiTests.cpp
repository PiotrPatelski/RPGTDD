#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiActionMock.hpp>
#include <ButtonListMock.hpp>
#include <WindowMock.hpp>
#include <EditorGui.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiTest : public testing::Test
{
    std::unique_ptr<EditorGui> sut;
};


TEST_F(EditorGuiTest, EditorGuiExecutesGivenAction)
{
    NiceMock<Events::GuiActionMock> guiAction;
    EXPECT_CALL(guiAction, execute(A<EditorGui&>()));
    sut = std::make_unique<EditorGui>();
    sut->acceptRequest(guiAction);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotUpdateAddedPauseMenuWhenNotPaused)
{
    auto pauseMenu = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    const sf::Vector2i currentMousePosition{30, 30};
    EXPECT_CALL(*pauseMenu, update(_)).Times(0);
    sut = std::make_unique<EditorGui>();
    sut->addPauseMenu(PauseMenu{std::move(pauseMenu), ::Types::Background{}});
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiUpdatesAddedPauseMenuWhenPaused)
{
    auto pauseMenu = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    const sf::Vector2i currentMousePosition{30, 30};
    EXPECT_CALL(*pauseMenu, update(Eq(currentMousePosition)));
    sut = std::make_unique<EditorGui>();
    sut->addPauseMenu(PauseMenu{std::move(pauseMenu), ::Types::Background{}});
    sut->togglePause();
    sut->update(currentMousePosition);
}

TEST_F(EditorGuiTest, EditorGuiDrawsAddedPauseMenuWhenPaused)
{
    auto pauseMenu = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    EXPECT_CALL(*pauseMenu, drawTo(A<::Types::Window&>()));
    sut = std::make_unique<EditorGui>();
    sut->addPauseMenu(PauseMenu{std::move(pauseMenu), ::Types::Background{}});
    sut->togglePause();
    NiceMock<::Types::WindowMock> window;
    sut->drawTo(window);
}

TEST_F(EditorGuiTest, EditorGuiDoesNotDrawAddedPauseMenuWhenNotPaused)
{
    auto pauseMenu = std::make_unique<NiceMock<Gui::ButtonListMock>>();
    EXPECT_CALL(*pauseMenu, drawTo(A<::Types::Window&>())).Times(0);
    sut = std::make_unique<EditorGui>();
    sut->addPauseMenu(PauseMenu{std::move(pauseMenu), ::Types::Background{}});
    NiceMock<::Types::WindowMock> window;
    sut->drawTo(window);
}

}