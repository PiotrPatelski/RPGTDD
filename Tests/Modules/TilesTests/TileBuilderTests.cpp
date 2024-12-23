#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileBuilderTest : public testing::Test
{
    const sf::Texture textureSheet;
    const std::vector<std::string> tileIds{"TILE1", "TILE2", "TILE3"};
    const uint tileBoxSize{64};
    const sf::Vector2i validPosition{20, 20};
};

TEST_F(TileBuilderTest, willThrowWhenBuildWontFindTileId)
{
    auto sut = DefaultTileBuilder{&textureSheet, tileIds, tileBoxSize}.atPosition(validPosition);
    ASSERT_THROW(sut.build("INVALID_ID"), std::out_of_range);
}

TEST_F(TileBuilderTest, buildsTileWithGivenPosition)
{
    DefaultTileBuilder sut(&textureSheet, tileIds, tileBoxSize);

    auto result = sut.atPosition(validPosition).build("TILE1");
    ASSERT_EQ(result->getPosition(), validPosition);
}

}