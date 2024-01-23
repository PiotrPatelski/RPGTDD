#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileField.hpp>
#include <TileMock.hpp>
#include <WindowMock.hpp>

namespace Tiles
{

using namespace ::testing;

struct TileFieldTest : public testing::Test
{
    const sf::Vector2i validPosition{325, 325};
    NiceMock<::Types::WindowMock> window;
};

TEST_F(TileFieldTest, createdEmptyTileField)
{
    TileField sut(validPosition);
    EXPECT_TRUE(sut.isEmpty());
    EXPECT_FALSE(sut.isFull());
}

TEST_F(TileFieldTest, tileFieldNotEmptyAfterTileAddition)
{
    TileField sut(validPosition);
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    EXPECT_FALSE(sut.isEmpty());
    EXPECT_FALSE(sut.isFull());
}

TEST_F(TileFieldTest, tileFieldFullAfterTileAddition)
{
    TileField sut(validPosition);
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    EXPECT_FALSE(sut.isEmpty());
    EXPECT_TRUE(sut.isFull());
}

TEST_F(TileFieldTest, tileFieldNotFullAfterRemovalFromFull)
{
    TileField sut(validPosition);
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    sut.pushTile(std::make_unique<NiceMock<TileMock>>());
    EXPECT_TRUE(sut.isFull());
    sut.popTile();
    EXPECT_FALSE(sut.isFull());
}

}