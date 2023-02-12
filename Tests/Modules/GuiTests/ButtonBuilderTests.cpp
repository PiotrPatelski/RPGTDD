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
        uint screenWidth = 1920;
        uint screenHeight = 1080;
        sut = std::make_unique<ButtonBuilder>(sf::VideoMode(screenWidth, screenHeight));
    }
    std::unique_ptr<IButtonBuilder> sut;
};

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithDefaultValues)
{
    auto button = sut->build();
    ASSERT_EQ(button->getTextContent().getString(), "");
    ASSERT_EQ(button->getTextContent().getCharacterSize(), 0);
    ASSERT_EQ(button->getPosition().x, 0.f);
    ASSERT_EQ(button->getPosition().y, 0.f);
    ASSERT_EQ(button->getSize().x, 0.f);
    ASSERT_EQ(button->getSize().y, 0.f);
    ASSERT_EQ(button->getFont().getInfo().family, "");
}
TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenTextContent)
{
    auto button = sut->withTextContent("New Game").build();
    ASSERT_EQ(button->getTextContent().getString(), "New Game");
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
    auto font = std::make_shared<sf::Font>();
    font->loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    auto button = sut->withFont(font).build();
    sut.reset();
    font.reset();
    ASSERT_EQ(button->getFont().getInfo().family, "xBONES");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithCalculatedCharacterSizeWhenButtonSizeIsNotZero)
{
    auto button = sut->withTextContent("New Game").withSize(9.f, 7.f).build();
    ASSERT_EQ(button->getTextContent().getCharacterSize(), 30);
}

TEST(ButtonBuilderHelperFunctionTest, calculatesFontSizeFromScreenResolution)
{
    const uint buttonWidth = 150.f;
    const uint buttonHeight = 90.f;
    const uint result = 30;
    ASSERT_EQ(calculateFontSize(sf::Vector2f(buttonWidth, buttonHeight)), result);
}

}