#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Button.hpp>

namespace Gui
{

const EventColor DEFAULT_TEXT_COLORS = EventColor{
    sf::Color(70, 70, 70, 200),
    sf::Color(250, 250, 150, 250),
    sf::Color(20, 20, 20, 50)};

const EventColor DEFAULT_BACKGROUND_COLORS = EventColor{
    sf::Color(70, 70, 70, 50),
    sf::Color(250, 250, 150, 50),
    sf::Color(20, 20, 20, 50)};

const EventColor TRANSPARENT_EVENT_COLORS = EventColor{
    sf::Color::Transparent,
    sf::Color::Transparent,
    sf::Color::Transparent};

struct MainMenuButtonTest : public testing::Test
{
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        sf::Font{},
        50,
        DEFAULT_TEXT_COLORS,
        DEFAULT_BACKGROUND_COLORS,
        TRANSPARENT_EVENT_COLORS);
};

TEST_F(MainMenuButtonTest, buttonWillReturnItsTextContent)
{
    ASSERT_EQ(sut->getTextContent().getString(), "Test");
}

TEST_F(MainMenuButtonTest, buttonStateWillRemainIdleWhenMousePosDoesNotIntersectWithBackground)
{
    sut->update(sf::Vector2i{280, 280});
    ASSERT_EQ(sut->getBackground().getFillColor(), DEFAULT_BACKGROUND_COLORS.idle);
}

TEST_F(MainMenuButtonTest, buttonStateWillChangeToHoverWhenMousePosIntersectsWithBackground)
{
    sut->update(sf::Vector2i{55, 55});
    ASSERT_EQ(sut->getBackground().getFillColor(), DEFAULT_BACKGROUND_COLORS.hover);
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