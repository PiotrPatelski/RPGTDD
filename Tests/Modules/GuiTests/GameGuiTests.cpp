#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <WindowMock.hpp>
#include <GameGui.hpp>
#include <GuiActionMock.hpp>

namespace Gui
{

using namespace ::testing;

struct GameGuiTest : public testing::Test
{
    std::unique_ptr<UserInterface> sut;
};


TEST_F(GameGuiTest, GameGuiExecutesGivenAction)
{
    NiceMock<Events::GuiActionMock> guiAction;
    EXPECT_CALL(guiAction, execute(A<GameGui&>()));
    sut = std::make_unique<GameGui>();
    sut->acceptRequest(guiAction);
}

}