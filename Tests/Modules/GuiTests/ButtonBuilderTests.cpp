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
        sut = std::make_unique<MainMenuButtonBuilder>(sf::VideoMode(screenWidth, screenHeight));
    }
    std::unique_ptr<IButtonBuilder> sut;
};

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithDefaultValues)
{
    auto button = sut->build();
    ASSERT_EQ(button->getTextContent(), "");
    ASSERT_EQ(button->getPosition().x, 0.f);
    ASSERT_EQ(button->getPosition().y, 0.f);
    ASSERT_EQ(button->getSize().x, 0.f);
    ASSERT_EQ(button->getSize().y, 0.f);
    ASSERT_EQ(button->getFont().getInfo().family, "");
}
TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenTextContent)
{
    auto button = sut->withTextContent("New Game").build();
    ASSERT_EQ(button->getTextContent(), "New Game");
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonAtGivenPosition)
{
    auto button = sut->atPosition(15.6f, 30.f).build();
    ASSERT_EQ(button->getPosition().x, 15.6f);
    ASSERT_EQ(button->getPosition().y, 30.f);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenSize)
{
    auto button = sut->withSize(13.f, 6.f).build();
    ASSERT_EQ(button->getSize().x, 13.f);
    ASSERT_EQ(button->getSize().y, 6.f);
}

TEST_F(ButtonBuilderTest, buttonBuilderCreatesButtonWithGivenFont)
{
    sf::Font font;
    font.loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    auto button = sut->withFont(font).build();
    ASSERT_EQ(button->getFont().getInfo().family, "xBONES");
}

}