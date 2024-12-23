#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiActions.hpp>
#include <EditorGui.hpp>

namespace Events
{

using namespace ::testing;

struct GuiActionsTest : public testing::Test
{

};

TEST_F(GuiActionsTest, guiIsPausedAfterPauseActionExecutesOnIt)
{
    Gui::EditorGui gui(Gui::PauseMenu{}, nullptr);
    EXPECT_FALSE(gui.isPaused());
    TogglePause{}.execute(gui);
    EXPECT_TRUE(gui.isPaused());
    TogglePause{}.execute(gui);
    EXPECT_FALSE(gui.isPaused());
}

}