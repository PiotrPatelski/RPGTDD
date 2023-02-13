#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GameGuiManager.hpp>
#include <ButtonBuilderMock.hpp>

namespace Gui
{

using namespace ::testing;

struct GameGuiManagerTest : public ::testing::Test
{

};

TEST_F(GameGuiManagerTest, emptyGameGuiManagerCreated)
{
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    auto sut = std::make_unique<GameGuiManager>(std::move(buttonBuilder));
}

}