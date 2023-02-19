#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <PauseMenuCalculator.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <Background.hpp>

namespace VectorMath
{

using namespace ::testing;

struct TextSizeCalculationsTest : public ::testing::TestWithParam<std::tuple<float, float, uint>>
{
    const sf::VideoMode resolution{1920, 1080};
    VectorMath::PauseMenuCalculator sut{resolution};
};

TEST_P(TextSizeCalculationsTest, calculatesDescriptionTextSizeForGivenBackgroundSize)
{
    const auto [backgroundWidth, backgroundHeight, expectedTextSize] = GetParam();

    const sf::Vector2f backgroundSize{backgroundWidth, backgroundHeight};
    const auto result = sut.calculateTextSize(backgroundSize);

    EXPECT_EQ(result, expectedTextSize);
}

INSTANTIATE_TEST_CASE_P(
    TextSizeCalculations,
    TextSizeCalculationsTest,
    Values(
        std::make_tuple(150.f, 90.f, 7),
        std::make_tuple(70.f, 30.f, 3),
        std::make_tuple(230.f, 150.f, 11),
        std::make_tuple(300.f, 600.f, 28),
        std::make_tuple(21.f, 37.f, 1),
        std::make_tuple(123.f, 456.f, 18),
        std::make_tuple(0.f, 456.f, 14)));

struct TextPositionCalculationsTest : public ::testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f>>
{
    const sf::VideoMode resolution{1920, 1080};
    VectorMath::PauseMenuCalculator sut{resolution};
};

TEST_P(TextPositionCalculationsTest, calculatesDescriptionTextSizeForGivenBackgroundSize)
{
    const auto [bgPixelSize, textSize, bgPixelPosition, expectedTextPosition] = GetParam();

    const auto backgroundSize = PixelsPoint(resolution, bgPixelSize);
    const auto backgroundPosition = PixelsPoint(resolution, bgPixelPosition);
    const ::Types::Background background{backgroundPosition, backgroundSize};
    const sf::FloatRect textRect{{0, 0}, textSize};

    const auto result = sut.calculateTextPosition(background, textRect);
    EXPECT_EQ(result.x, expectedTextPosition.x);
    EXPECT_EQ(result.y, expectedTextPosition.y);
}

INSTANTIATE_TEST_CASE_P(
    TextPositionCalculations,
    TextPositionCalculationsTest,
    Values(
        std::make_tuple(sf::Vector2f{150.f, 90.f}, sf::Vector2f{130.f, 20.f}, sf::Vector2f{600.f, 700.f}, sf::Vector2f{610.f, 721.6}),
        std::make_tuple(sf::Vector2f{400.f, 600.f}, sf::Vector2f{130.f, 20.f}, sf::Vector2f{600.f, 700.f}, sf::Vector2f{735.f, 721.6}),
        std::make_tuple(sf::Vector2f{150.f, 90.f}, sf::Vector2f{70.f, 40.f}, sf::Vector2f{600.f, 700.f}, sf::Vector2f{640.f, 721.6}),
        std::make_tuple(sf::Vector2f{150.f, 90.f}, sf::Vector2f{130.f, 20.f}, sf::Vector2f{200.f, 31.f}, sf::Vector2f{210.f, 52.6}),
        std::make_tuple(sf::Vector2f{632.f, 200.f}, sf::Vector2f{21.f, 37.f}, sf::Vector2f{666.f, 200.f}, sf::Vector2f{971.5, 221.6})));

struct FirstSectionPositionCalculationsTest : public ::testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f>>
{
    const sf::VideoMode resolution{1920, 1080};
    VectorMath::PauseMenuCalculator sut{resolution};
};

TEST_P(FirstSectionPositionCalculationsTest, calculatesPositionOfSectionWhenItsAddedAsFirstOne)
{
    const auto [bgPixelSize, bgPixelPosition, expectedSectionPosition] = GetParam();

    const auto backgroundSize = PixelsPoint(resolution, bgPixelSize);
    const auto backgroundPosition = PixelsPoint(resolution, bgPixelPosition);
    const ::Types::Background background{backgroundPosition, backgroundSize};

    const auto result = sut.calculatePositionWithNoButtons(background);
    EXPECT_NEAR(result.toPixels().x, expectedSectionPosition.x, 1);
    EXPECT_NEAR(result.toPixels().y, expectedSectionPosition.y, 1);
}

INSTANTIATE_TEST_CASE_P(
    MenuSectionPositionCalculations,
    FirstSectionPositionCalculationsTest,
    Values(
        std::make_tuple(sf::Vector2f{150.f, 90.f}, sf::Vector2f{600.f, 700.f}, sf::Vector2f{637.5, 712.8}),
        std::make_tuple(sf::Vector2f{400.f, 600.f}, sf::Vector2f{1500.f, 700.f}, sf::Vector2f{1600, 785.7}),
        std::make_tuple(sf::Vector2f{150.f, 90.f}, sf::Vector2f{32.f, 7.f}, sf::Vector2f{69.5, 19.8}),
        std::make_tuple(sf::Vector2f{920.f, 108.f}, sf::Vector2f{1200.f, 31.f}, sf::Vector2f{1430.f, 46.4}),
        std::make_tuple(sf::Vector2f{632.f, 200.f}, sf::Vector2f{3.f, 800.f}, sf::Vector2f{161.f, 828.5})));

struct NextSectionPositionCalculationsTest : public ::testing::TestWithParam
    <std::tuple<sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f>>
{
    const sf::VideoMode resolution{1920, 1080};
    VectorMath::PauseMenuCalculator sut{resolution};
};

TEST_P(NextSectionPositionCalculationsTest, calculatesPositionOfSectionInRelationToPreviouslyAddedOne)
{
    const auto [bgPixelSize, bgPixelPosition,
                firstButtonSPPosition, lastButtonSPPosition,
                lastButtonSPSize, expectedSectionPosition] = GetParam();

    const auto backgroundSize = PixelsPoint(resolution, bgPixelSize);
    const auto backgroundPosition = PixelsPoint(resolution, bgPixelPosition);
    const ::Types::Background background{backgroundPosition, backgroundSize};

    const VectorMath::ScreenPercentagePoint firstButtonPosition(resolution, firstButtonSPPosition);
    const VectorMath::ScreenPercentagePoint lastButtonPosition(resolution, lastButtonSPPosition);
    const VectorMath::ScreenPercentagePoint lastButtonSize(resolution, lastButtonSPSize);

    const auto result = sut.calculatePositionRelativeToButtons(firstButtonPosition, lastButtonPosition, lastButtonSize, background);
    EXPECT_NEAR(result.value().x, expectedSectionPosition.x, 1);
    EXPECT_NEAR(result.value().y, expectedSectionPosition.y, 1);
}

INSTANTIATE_TEST_CASE_P(
    MenuSectionPositionCalculations,
    NextSectionPositionCalculationsTest,
    Values(
        std::make_tuple(sf::Vector2f{500.f, 700.f}, sf::Vector2f{500.f, 700.f}, 
                        sf::Vector2f{150.f, 90.f}, sf::Vector2f{150.f, 90.f}, 
                        sf::Vector2f{200.f, 130.f}, sf::Vector2f{150.f, 245.2}),

        std::make_tuple(sf::Vector2f{500.f, 700.f}, sf::Vector2f{500.f, 700.f}, 
                        sf::Vector2f{150.f, 90.f}, sf::Vector2f{150.f, 245.2}, 
                        sf::Vector2f{200.f, 130.f}, sf::Vector2f{150.5, 400.4}),

        std::make_tuple(sf::Vector2f{632.f, 586.f}, sf::Vector2f{500.f, 700.f}, 
                        sf::Vector2f{150.f, 90.f}, sf::Vector2f{150.f, 90.f}, 
                        sf::Vector2f{200.f, 130.f}, sf::Vector2f{150.5, 245.2}),

        std::make_tuple(sf::Vector2f{890.f, 700.f}, sf::Vector2f{500.f, 700.f}, 
                        sf::Vector2f{150.f, 90.f}, sf::Vector2f{150.f, 90.f}, 
                        sf::Vector2f{300.f, 260.f}, sf::Vector2f{150.5, 375.2})));
}