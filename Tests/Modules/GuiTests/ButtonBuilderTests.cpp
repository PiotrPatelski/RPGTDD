#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <ButtonTextCalculations.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Gui
{

struct ButtonBuilderTest : public testing::Test
{
    ButtonBuilderTest()
    {
        sut = std::make_unique<MenuButtonBuilder>();
    }
    sf::VideoMode resolution{1920, 1080};
    std::unique_ptr<ButtonBuilder> sut;
};

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithDefaultValues)
{
    auto button = sut->build();
    ASSERT_EQ(button->getTextContent(), std::nullopt);
    ASSERT_EQ(button->getPosition().value().x, 0.f);
    ASSERT_EQ(button->getPosition().value().y, 0.f);
    ASSERT_EQ(button->getSize().value().x, 0.f);
    ASSERT_EQ(button->getSize().value().y, 0.f);
    ASSERT_EQ(button->getFont(), std::nullopt);
}
TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenTextContent)
{
    auto button = sut->withTextContent(sf::Text("New Game", sf::Font{})).build();
    const auto buttonText = button->getTextContent();
    ASSERT_NE(buttonText, std::nullopt);
    ASSERT_EQ(buttonText->getString(), "New Game");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonAtPixelPositionGivenInScreenPercentagePoint)
{
    const float xInScreenPerc = 15.6f;
    const float yInScreenPerc = 30.f;

    const float xInPixels = 299.52;
    const float yInPixels = 324;

    auto button = sut->atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(xInScreenPerc, yInScreenPerc))).build();

    ASSERT_EQ(button->getPosition().toPixels().x, xInPixels);
    ASSERT_EQ(button->getPosition().toPixels().y, yInPixels);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithPixelSizeGivenInScreenPercentagePoint)
{
    const float widthInScreenPerc = 13.f;
    const float heightInScreenPerc = 6.f;

    const float widthInPixels = 249.6;
    const float heightInPixels = 64.8;

    auto button = sut->withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(widthInScreenPerc, heightInScreenPerc))).build();

    ASSERT_EQ(button->getSize().toPixels().x, widthInPixels);
    ASSERT_EQ(button->getSize().toPixels().y, heightInPixels);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenFont)
{
    sf::Font font;
    font.loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    sut = std::make_unique<MenuButtonBuilder>();
    auto button = sut->withTextContent(sf::Text("test", font)).build();
    sut.reset();
    const auto returnedFont = button->getFont();
    ASSERT_NE(returnedFont, std::nullopt);
    ASSERT_EQ(returnedFont->getInfo().family, "xBONES");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithCalculatedCharacterSizeWhenButtonSizeIsNotZero)
{
    auto button = sut->withTextContent(sf::Text("New Game", sf::Font{})).
        withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(9.f, 7.f))).build();
    const auto buttonText = button->getTextContent();
    ASSERT_NE(buttonText, std::nullopt);
    ASSERT_EQ(buttonText->getCharacterSize(), 31);
}

}