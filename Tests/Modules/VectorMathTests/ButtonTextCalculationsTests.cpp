#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonTextCalculations.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <Background.hpp>

namespace VectorMath
{

using namespace ::testing;

struct FontSizeCalculationsTest : public ::testing::TestWithParam<std::tuple<uint, uint, uint>>
{};


TEST_P(FontSizeCalculationsTest, calculatesFontSizeFromButtonSize)
{
    const auto [buttonWidth, buttonHeight, expectedFontSize] = GetParam();

    EXPECT_EQ(VectorMath::calculateFontSize(sf::Vector2f(buttonWidth, buttonHeight)), expectedFontSize);
}

INSTANTIATE_TEST_CASE_P(
    FontSizeCalculations,
    FontSizeCalculationsTest,
    Values(
        std::make_tuple(150.f, 90.f, 30),
        std::make_tuple(70.f, 30.f, 12),
        std::make_tuple(230.f, 150.f, 47),
        std::make_tuple(300.f, 600.f, 112),
        std::make_tuple(21.f, 37.f, 7),
        std::make_tuple(123.f, 456.f, 72)));


struct TextPositioningOnButtonBackgroundTest : public ::testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f>>
{
    const sf::VideoMode resolution{1920, 1080};
};

TEST_P(TextPositioningOnButtonBackgroundTest, calculatesTextRectPositionForGivenBackground)
{
    const auto [textSize, bgPixelSize, bgPixelPosition, expectedTextPosition] = GetParam();

    const sf::FloatRect textRect{{0, 0}, textSize};
    const auto backgroundSize = PixelsPoint(resolution, bgPixelSize);
    const auto backgroundPosition = PixelsPoint(resolution, bgPixelPosition);
    ::Types::Background background{backgroundPosition, backgroundSize};

    const auto result = VectorMath::calculateTextPosOnBackground(background, textRect);

    EXPECT_EQ(result.x, expectedTextPosition.x);
    EXPECT_EQ(result.y, expectedTextPosition.y);
}

INSTANTIATE_TEST_CASE_P(
    TextPositionCalculations,
    TextPositioningOnButtonBackgroundTest,
    Values(
        std::make_tuple(sf::Vector2f{400.f, 100.f}, sf::Vector2f{500.f, 800.f}, sf::Vector2f{710.f, 200.f}, sf::Vector2f{761.f, 200.f}),
        std::make_tuple(sf::Vector2f{200.f, 100.f}, sf::Vector2f{300.f, 200.f}, sf::Vector2f{200.f, 710.f}, sf::Vector2f{251.f, 710.f}),
        std::make_tuple(sf::Vector2f{100.f, 60.f}, sf::Vector2f{100.f, 50.f}, sf::Vector2f{823.f, 50.f}, sf::Vector2f{824.f, 50.f}),
        std::make_tuple(sf::Vector2f{660.f, 230.f}, sf::Vector2f{620.f, 490.f}, sf::Vector2f{1009.f, 1000.f}, sf::Vector2f{990.f, 1000.f}),
        std::make_tuple(sf::Vector2f{233.f, 232.f}, sf::Vector2f{210.f, 210.f}, sf::Vector2f{666.f, 21.f}, sf::Vector2f{655.5, 21.f}),
        std::make_tuple(sf::Vector2f{111.f, 777.f}, sf::Vector2f{770.f, 400.f}, sf::Vector2f{21.f, 37.f}, sf::Vector2f{351.5, 37.f}),
        std::make_tuple(sf::Vector2f{213.f, 700.f}, sf::Vector2f{1110.f, 666.f}, sf::Vector2f{504.f, 356.f}, sf::Vector2f{953.5, 356.f}),
        std::make_tuple(sf::Vector2f{333.f, 333.f}, sf::Vector2f{2137.f, 420.f}, sf::Vector2f{76.f, 200.f}, sf::Vector2f{979.f, 200.f})));

}