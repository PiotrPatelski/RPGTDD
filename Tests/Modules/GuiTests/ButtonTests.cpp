#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Button.hpp>

namespace Gui
{

struct MainMenuButtonTest : public testing::Test
{
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(0, 0),
        sf::Vector2f(0, 0),
        "Test",
        sf::Font{},
        50,
        EventColor{},
        EventColor{},
        EventColor{});
};

TEST_F(MainMenuButtonTest, buttonWillReturnItsTextContent)
{
    ASSERT_EQ(sut->getTextContent().getString(), "Test");
}

TEST(MainMenuButtonHelperFunctionTest, calculateTextPosOnGivenBackground)
{
    sf::RectangleShape background;
    background.setPosition(15.6f, 40);
    background.setSize(sf::Vector2f(13.f, 6.f));
    sf::Text text;
    text.setCharacterSize(50);
    ASSERT_EQ(calculateTextPosOnBackground(background, text).x, 22.1f);
    ASSERT_EQ(calculateTextPosOnBackground(background, text).y, 40.f);
}

}