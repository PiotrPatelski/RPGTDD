#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileBuilderTest : public testing::Test
{
    const sf::Texture textureSheet;
    const std::vector<std::string> tileIds;
};

TEST_F(TileBuilderTest, buildsTileWithGivenPosition)
{
    DefaultTileBuilder sut(&textureSheet, tileIds);

    const sf::Vector2i position{20, 20};
    auto result = sut.atPosition(position).build();
    ASSERT_EQ(result->getPosition(), position);
}

}