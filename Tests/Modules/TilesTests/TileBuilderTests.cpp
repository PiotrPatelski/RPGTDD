#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileBuilderTest : public testing::Test
{

};

TEST_F(TileBuilderTest, buildsTileWithGivenPosition)
{
    const sf::Texture textureSheet;
    DefaultTileBuilder sut(&textureSheet);

    const sf::Vector2i position{20, 20};
    auto result = sut.atPosition(position).build();
    ASSERT_EQ(result->getPosition(), position);
}

}