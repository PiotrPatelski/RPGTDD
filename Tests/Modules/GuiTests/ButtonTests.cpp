#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Button.hpp>
#include <ButtonEventHandlerMock.hpp>
#include <State.hpp>

namespace Gui
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;

EventColor TEST_IDLE_COLORS = EventColor{
    sf::Color(70, 70, 70, 200),
    sf::Color(70, 70, 70, 50),
    sf::Color::Transparent};

EventColor TEST_HOVER_COLORS = EventColor{
    sf::Color(250, 250, 150, 250),
    sf::Color(250, 250, 150, 50),
    sf::Color::Transparent};

EventColor TEST_ACTIVE_COLORS = EventColor{
    sf::Color(20, 20, 20, 50),
    sf::Color(20, 20, 20, 50),
    sf::Color::Transparent};

struct MainMenuButtonTest : public testing::Test
{

};

TEST_F(MainMenuButtonTest, buttonWillReturnItsTextContent)
{
    std::unique_ptr<NiceMock<Events::ButtonEventHandlerMock>> eventHandler = std::make_unique<NiceMock<Events::ButtonEventHandlerMock>>();
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        std::make_shared<sf::Font>(),
        50,
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(eventHandler));
    ASSERT_EQ(sut->getTextContent().getString(), "Test");
}

TEST_F(MainMenuButtonTest, buttonStateWillRemainIdleWhenMousePosDoesNotIntersectWithBackground)
{
    std::unique_ptr<NiceMock<Events::ButtonEventHandlerMock>> eventHandler = std::make_unique<NiceMock<Events::ButtonEventHandlerMock>>();
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        std::make_shared<sf::Font>(),
        50,
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(eventHandler));
    sut->update(sf::Vector2i{280, 280});
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_IDLE_COLORS.background);
}

TEST_F(MainMenuButtonTest, buttonStateWillChangeToHoverWhenMousePosIntersectsWithBackground)
{
    std::unique_ptr<NiceMock<Events::ButtonEventHandlerMock>> eventHandler = std::make_unique<NiceMock<Events::ButtonEventHandlerMock>>();
    EXPECT_CALL(*eventHandler, isPressed()).WillOnce(Return(false));
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        std::make_shared<sf::Font>(),
        50,
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(eventHandler));
    sut->update(sf::Vector2i{55, 55});
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_HOVER_COLORS.background);
}

TEST_F(MainMenuButtonTest, buttonStateWillChangeToActiveWhenMousePosIntersectsWithBackgroundAndIsPressed)
{
    std::unique_ptr<NiceMock<Events::ButtonEventHandlerMock>> eventHandler = std::make_unique<NiceMock<Events::ButtonEventHandlerMock>>();
    EXPECT_CALL(*eventHandler, isPressed()).WillOnce(Return(true));
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        std::make_shared<sf::Font>(),
        50,
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(eventHandler));
    sut->update(sf::Vector2i{55, 55});
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_ACTIVE_COLORS.background);
}

TEST_F(MainMenuButtonTest, buttonIndicatesThatIsPressedWhenEventHandlerReceivesSfMouseSignal)
{
    std::unique_ptr<NiceMock<Events::ButtonEventHandlerMock>> eventHandler = std::make_unique<NiceMock<Events::ButtonEventHandlerMock>>();
    EXPECT_CALL(*eventHandler, isPressed()).WillOnce(Return(true));
    std::unique_ptr<IButton> sut = std::make_unique<MainMenuButton>(
        sf::Vector2f(50, 50),
        sf::Vector2f(50, 50),
        "Test",
        std::make_shared<sf::Font>(),
        50,
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(eventHandler));
    sut->update(sf::Vector2i{55, 55});
    ASSERT_TRUE(sut->isPressed());
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