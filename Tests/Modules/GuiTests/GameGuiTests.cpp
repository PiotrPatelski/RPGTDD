#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <WindowMock.hpp>
#include <GameGui.hpp>

namespace Gui
{

using namespace ::testing;

struct GameGuiTest : public testing::Test
{
    std::unique_ptr<UserInterface> sut;
};


TEST_F(GameGuiTest, emptyGameGuiCreated)
{
    sut = std::make_unique<GameGui>();
}

}