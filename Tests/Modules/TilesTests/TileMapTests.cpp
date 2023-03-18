#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>
#include <TileMap.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileMapTest : public testing::Test
{
    const float tileBoxSize{64.f};
    const uint tileAmountOnX{10};
    const uint tileAmountOnY{10};
    const sf::Vector2i validPosition{325, 325};
    const sf::Vector2i invalidPosition{720, 720};
    const sf::Vector2i negativePosition{-10, -10};
    TileBuilder builder;
};

TEST_F(TileMapTest, tileMapValidatesPositionWithinBounds)
{
    TileMap sut(tileBoxSize, tileAmountOnX, tileAmountOnY);
    EXPECT_TRUE(sut.isValidPosition(validPosition));
}

TEST_F(TileMapTest, tileMapValidatesPositionOutsideBounds)
{
    TileMap sut(tileBoxSize, tileAmountOnX, tileAmountOnY);
    EXPECT_FALSE(sut.isValidPosition(invalidPosition));
}

TEST_F(TileMapTest, tileMapValidatesNegativePosition)
{
    TileMap sut(tileBoxSize, tileAmountOnX, tileAmountOnY);
    EXPECT_FALSE(sut.isValidPosition(negativePosition));
}

TEST_F(TileMapTest, tileMapEmptyTilePositionThrowsWhenPositionIsInvalid)
{
    TileMap sut(tileBoxSize, tileAmountOnX, tileAmountOnY);
    EXPECT_THROW(sut.isEmptyAt(invalidPosition), std::out_of_range);
    EXPECT_THROW(sut.isEmptyAt(negativePosition), std::out_of_range);
}

TEST_F(TileMapTest, tileMapEmptyAtPositionWhereNoTileWasAdded)
{
    TileMap sut(tileBoxSize, tileAmountOnX, tileAmountOnY);
    const sf::Vector2i someRandomTilePosition{0, 0};
    EXPECT_TRUE(sut.isEmptyAt(someRandomTilePosition));
}

}