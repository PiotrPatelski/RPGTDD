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
    sf::Texture texture;
    NormalTile sut(&texture);

    EXPECT_CALL(window, draw(A<const sf::Drawable&>()));
    sut.drawTo(window);
}

}