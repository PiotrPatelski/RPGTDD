#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiActionMock.hpp>
#include <EditorGui.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiTest : public testing::Test
{
    std::unique_ptr<UserInterface> sut;
};


TEST_F(EditorGuiTest, EditorGuiExecutesGivenAction)
{
    NiceMock<Events::GuiActionMock> guiAction;
    EXPECT_CALL(guiAction, execute(A<EditorGui&>()));
    sut = std::make_unique<EditorGui>();
    sut->acceptRequest(guiAction);
}

}