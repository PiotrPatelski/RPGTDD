#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Gui
{

struct ButtonBuilderTest : public testing::Test
{
    ButtonBuilderTest()
    {
        sut = std::make_unique<MenuButtonBuilder>(sf::VideoMode(screenWidth, screenHeight));
    }
    uint screenWidth = 1920;
    uint screenHeight = 1080;
    std::unique_ptr<ButtonBuilder> sut;
};

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithDefaultValues)
{
    auto button = sut->build();
    ASSERT_EQ(button->getTextContent(), std::nullopt);
    ASSERT_EQ(button->getPosition().x, 0.f);
    ASSERT_EQ(button->getPosition().y, 0.f);
    ASSERT_EQ(button->getSize().x, 0.f);
    ASSERT_EQ(button->getSize().y, 0.f);
    ASSERT_EQ(button->getFont(), std::nullopt);
}
TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenTextContent)
{
    auto button = sut->withTextContent(sf::Text("New Game", sf::Font{})).build();
    const auto buttonText = button->getTextContent();
    ASSERT_NE(buttonText, std::nullopt);
    ASSERT_EQ(buttonText->getString(), "New Game");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonAtPixelPositionGivenInScreenPercentage)
{
    const float xInScreenPerc = 15.6f;
    const float yInScreenPerc = 30.f;

    const uint xInPixels = 299;
    const uint yInPixels = 324;

    auto button = sut->atPosition(xInScreenPerc, yInScreenPerc).build();

    ASSERT_EQ(button->getPosition().x, xInPixels);
    ASSERT_EQ(button->getPosition().y, yInPixels);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithPixelSizeGivenInScreenPercentage)
{
    const float widthInScreenPerc = 13.f;
    const float heightInScreenPerc = 6.f;

    const float widthInPixels = 249;
    const float heightInPixels = 64;

    auto button = sut->withSize(widthInScreenPerc, heightInScreenPerc).build();

    ASSERT_EQ(button->getSize().x, widthInPixels);
    ASSERT_EQ(button->getSize().y, heightInPixels);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenFont)
{
    sf::Font font;
    font.loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    sut = std::make_unique<MenuButtonBuilder>(sf::VideoMode(screenWidth, screenHeight));
    auto button = sut->withTextContent(sf::Text("test", font)).build();
    sut.reset();
    const auto returnedFont = button->getFont();
    ASSERT_NE(returnedFont, std::nullopt);
    ASSERT_EQ(returnedFont->getInfo().family, "xBONES");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithCalculatedCharacterSizeWhenButtonSizeIsNotZero)
{
    auto button = sut->withTextContent(sf::Text("New Game", sf::Font{})).withSize(9.f, 7.f).build();
    const auto buttonText = button->getTextContent();
    ASSERT_NE(buttonText, std::nullopt);
    ASSERT_EQ(buttonText->getCharacterSize(), 30);
}

TEST(ButtonBuilderHelperFunctionTest, calculatesFontSizeFromScreenResolution)
{
    const uint buttonWidth = 150.f;
    const uint buttonHeight = 90.f;
    const uint result = 30;
    ASSERT_EQ(calculateFontSize(sf::Vector2f(buttonWidth, buttonHeight)), result);
}

}