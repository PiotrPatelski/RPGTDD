#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>
#include <TileMap.hpp>
#include <TileMock.hpp>
#include <WindowMock.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileMapTest : public testing::Test
{
    const uint tileBoxSize{64};
    const uint tileAmountOnX{10};
    const uint tileAmountOnY{10};
    const sf::Vector2i validPosition{325, 325};
    const sf::Vector2i invalidPosition{720, 720};
    const sf::Vector2i negativePosition{-10, -10};
    NiceMock<::Types::WindowMock> window;
    TileBuilder builder;
    TileMap sut{tileBoxSize, tileAmountOnX, tileAmountOnY};
};

TEST_F(TileMapTest, tileMapValidatesPositionWithinBounds)
{
    EXPECT_TRUE(sut.isValidPosition(validPosition));
}

TEST_F(TileMapTest, tileMapValidatesPositionOutsideBounds)
{
    EXPECT_FALSE(sut.isValidPosition(invalidPosition));
}

TEST_F(TileMapTest, tileMapValidatesNegativePosition)
{
    EXPECT_FALSE(sut.isValidPosition(negativePosition));
}

TEST_F(TileMapTest, tileMapEmptyTilePositionThrowsWhenPositionIsInvalid)
{
    EXPECT_THROW(sut.isEmptyAt(invalidPosition), std::out_of_range);
    EXPECT_THROW(sut.isEmptyAt(negativePosition), std::out_of_range);
}

TEST_F(TileMapTest, tileMapEmptyAtPositionWhereNoTileWasAdded)
{
    const sf::Vector2i someRandomTilePosition{0, 0};
    EXPECT_TRUE(sut.isEmptyAt(someRandomTilePosition));
}

TEST_F(TileMapTest, tileMapAdditionThrowsWhenPositionIsInvalid)
{
    auto tile1 = std::make_unique<NiceMock<TileMock>>();
    auto tile2 = std::make_unique<NiceMock<TileMock>>();

    EXPECT_THROW(sut.addTile(std::move(tile1), invalidPosition), std::out_of_range);
    EXPECT_THROW(sut.addTile(std::move(tile2), negativePosition), std::out_of_range);
}

TEST_F(TileMapTest, tileMapNotEmptyAtPositionWhereTileWasAdded)
{
    const sf::Vector2i notRandomTilePosition{72, 72};
    auto tile = std::make_unique<NiceMock<TileMock>>();

    sut.addTile(std::move(tile), notRandomTilePosition);
    EXPECT_FALSE(sut.isEmptyAt(notRandomTilePosition));
}

TEST_F(TileMapTest, tileMapEmptyAtPositionWhereTileWasRemoved)
{
    const sf::Vector2i notRandomTilePosition{72, 72};
    auto tile = std::make_unique<NiceMock<TileMock>>();

    sut.addTile(std::move(tile), notRandomTilePosition);
    EXPECT_FALSE(sut.isEmptyAt(notRandomTilePosition));

    sut.removeTile(notRandomTilePosition);
    EXPECT_TRUE(sut.isEmptyAt(notRandomTilePosition));
}

TEST_F(TileMapTest, tileMapCannotAddMoreThanThreeTilesToAField)
{
    auto tile1 = std::make_unique<NiceMock<TileMock>>();
    auto tile2 = std::make_unique<NiceMock<TileMock>>();
    auto tile3 = std::make_unique<NiceMock<TileMock>>();
    auto tile4 = std::make_unique<NiceMock<TileMock>>();
    EXPECT_CALL(*tile1, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile2, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile3, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile4, drawTo(A<::Types::Window&>())).Times(0);

    sut.addTile(std::move(tile1), validPosition);
    sut.addTile(std::move(tile2), validPosition);
    sut.addTile(std::move(tile3), validPosition);
    sut.addTile(std::move(tile4), validPosition);

    sut.drawTo(window);
}

TEST_F(TileMapTest, tileMapUpdatesTilesAtDifferentFields)
{
    auto tile1 = std::make_unique<NiceMock<TileMock>>();
    auto tile2 = std::make_unique<NiceMock<TileMock>>();
    auto tile3 = std::make_unique<NiceMock<TileMock>>();
    auto tile4 = std::make_unique<NiceMock<TileMock>>();
    EXPECT_CALL(*tile1, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile2, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile3, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tile4, drawTo(A<::Types::Window&>()));

    const sf::Vector2i position1{0, 0};
    const sf::Vector2i position2{70, 70};
    const sf::Vector2i position3{0, 120};
    const sf::Vector2i position4{280, 460};
    sut.addTile(std::move(tile1), position1);
    sut.addTile(std::move(tile2), position2);
    sut.addTile(std::move(tile3), position3);
    sut.addTile(std::move(tile4), position4);

    sut.drawTo(window);
}

}