#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Tile.hpp>
#include <WindowMock.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileTest : public testing::Test
{
    NiceMock<::Types::WindowMock> window;
};

TEST_F(TileTest, tileFieldDelegatesDrawingToWindow)
{
    NormalTile sut(sf::Sprite(sf::Texture{}));

    EXPECT_CALL(window, draw(A<const sf::Drawable&>()));
    sut.drawTo(window);
}

}