#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>

namespace VectorMath
{

using namespace ::testing;
using TestParams = std::pair<sf::Vector2f, sf::Vector2f>;

struct ScreenPercentageToPixelsTest : public ::testing::TestWithParam<TestParams>
{
    const sf::VideoMode resolution{1920, 1080};
};

TEST_P(ScreenPercentageToPixelsTest, convertsResolutionPercentageToPixels)
{
    const auto [percentageValue, expectedPixelsValue] = GetParam();

    const auto calculatedResult = VectorMath::ScreenPercentagePoint(resolution, percentageValue).toPixels();
    EXPECT_NEAR(calculatedResult.x, expectedPixelsValue.x, 1);
    EXPECT_NEAR(calculatedResult.y, expectedPixelsValue.y, 1);
}

INSTANTIATE_TEST_CASE_P(
    PercentageToPixelsTest,
    ScreenPercentageToPixelsTest,
    Values(
        TestParams{{10.f, 10.f}, {192.f, 108.f}},
        TestParams{{3.f, 3.f}, {57.6, 32.4}},
        TestParams{{99.f, 1.f}, {1900.8, 10.8}},
        TestParams{{99.f, 99.f}, {1900.8, 1069.2}},
        TestParams{{-70.f, 5.f}, {-1344.f, 54.f}},
        TestParams{{0.f, 60.f}, {0, 648.f}},
        TestParams{{23.f, 0.f}, {441.6, 0}},
        TestParams{{120.f, 37.f}, {2304.f, 399.6}},
        TestParams{{24.f, 110.f}, {460.8, 1188.f}}));

struct ScreenPercentageFromPixelsPointTest : public ::testing::TestWithParam<TestParams>
{
    const sf::VideoMode resolution{1920, 1080};
};

TEST_P(ScreenPercentageFromPixelsPointTest, convertsPixelsPointToResolutionPercentage)
{
    const auto [expectedPercentageValue, pixelsVec] = GetParam();

    const VectorMath::PixelsPoint pixelsValue(resolution, pixelsVec);

    const auto calculatedResult = VectorMath::ScreenPercentagePoint(pixelsValue).value();
    EXPECT_NEAR(calculatedResult.x, expectedPercentageValue.x, 1);
    EXPECT_NEAR(calculatedResult.y, expectedPercentageValue.y, 1);
}

INSTANTIATE_TEST_CASE_P(
    PercentageToPixelsTest,
    ScreenPercentageFromPixelsPointTest,
    Values(
        TestParams{{10.f, 10.f}, {192.f, 108.f}},
        TestParams{{3.f, 3.f}, {57.6, 32.4}},
        TestParams{{99.f, 1.f}, {1900.8, 10.8}},
        TestParams{{99.f, 99.f}, {1900.8, 1069.2}},
        TestParams{{-16.6, 5.f}, {-320.f, 54.f}},
        TestParams{{0.f, 60.f}, {0, 648.f}},
        TestParams{{23.f, 0.f}, {441.6, 0}},
        TestParams{{104.6, 37.f}, {2000.f, 399.6}},
        TestParams{{24.f, 138.9}, {460.8, 1500.f}}));

}