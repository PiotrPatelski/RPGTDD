#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TilePositionGenerator.hpp>

namespace Tiles
{

using namespace ::testing;

bool isResultAMultiplicationOf(const uint result, const uint multiplier)
{
    return (result % multiplier) == 0;
}

struct TilePositionGeneratorTest : public testing::Test
{
    const uint tileAmountBeforeXIncrement = 10;
    const uint TileSizeInPixels = 64;
};

TEST_F(TilePositionGeneratorTest, eachNextGeneratedPositionIsAMultiplicationOfTileSize)
{
    TilePositionGenerator generator{tileAmountBeforeXIncrement, TileSizeInPixels};
    auto result = generator.generate();
    EXPECT_TRUE(isResultAMultiplicationOf(result.x, TileSizeInPixels));
    EXPECT_TRUE(isResultAMultiplicationOf(result.y, TileSizeInPixels));
    result = generator.generate();
    EXPECT_TRUE(isResultAMultiplicationOf(result.x, TileSizeInPixels));
    EXPECT_TRUE(isResultAMultiplicationOf(result.y, TileSizeInPixels));
    result = generator.generate();
    EXPECT_TRUE(isResultAMultiplicationOf(result.x, TileSizeInPixels));
    EXPECT_TRUE(isResultAMultiplicationOf(result.y, TileSizeInPixels));
    result = generator.generate();
    EXPECT_TRUE(isResultAMultiplicationOf(result.x, TileSizeInPixels));
    EXPECT_TRUE(isResultAMultiplicationOf(result.y, TileSizeInPixels));
    result = generator.generate();
    EXPECT_TRUE(isResultAMultiplicationOf(result.x, TileSizeInPixels));
    EXPECT_TRUE(isResultAMultiplicationOf(result.y, TileSizeInPixels));
}

TEST_F(TilePositionGeneratorTest, positionYIsIncrementedByTileSizeWithLessGenerationsThanThreshold)
{
    TilePositionGenerator generator{tileAmountBeforeXIncrement, TileSizeInPixels};
    auto result = generator.generate();
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 0);
    result = generator.generate();
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 64);
    result = generator.generate();
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 128);
}

TEST_F(TilePositionGeneratorTest, positionXIsIncrementedByTileSizeAndPositionYZeroedWhenGenerationIsRepeatedMoreTimesThanThreshold)
{
    const uint tileAmountUntilXIsIncremented{2};
    TilePositionGenerator generator{tileAmountUntilXIsIncremented, TileSizeInPixels};
    auto result = generator.generate();
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 0);
    result = generator.generate();
    EXPECT_EQ(result.x, 0);
    EXPECT_EQ(result.y, 64);
    result = generator.generate();
    EXPECT_EQ(result.x, 64);
    EXPECT_EQ(result.y, 0);
    result = generator.generate();
    EXPECT_EQ(result.x, 64);
    EXPECT_EQ(result.y, 64);
}

}
