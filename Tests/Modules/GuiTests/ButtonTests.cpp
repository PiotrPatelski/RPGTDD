#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Button.hpp>
#include <MouseEventListenerMock.hpp>
#include <State.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <ButtonTextCalculations.hpp>

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
    const sf::VideoMode resolution{480, 480};
    const VectorMath::ScreenPercentagePoint position{resolution, sf::Vector2f(50, 50)};
    const VectorMath::ScreenPercentagePoint size{resolution, sf::Vector2f(50, 50)};
    const std::string name{"test"};
    const uint characterSize{50};

};

TEST_F(MainMenuButtonTest, buttonWillReturnItsTextContent)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    const auto buttonText = sut->getTextContent();
    ASSERT_NE(buttonText, std::nullopt);
    ASSERT_EQ(buttonText->getString(), name);
}

TEST_F(MainMenuButtonTest, buttonWillReturnItsSize)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    ASSERT_FLOAT_EQ(sut->getSize().value().x, size.value().x);
    ASSERT_FLOAT_EQ(sut->getSize().value().y, size.value().y);
}

TEST_F(MainMenuButtonTest, buttonWillReturnItsPosition)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    ASSERT_FLOAT_EQ(sut->getPosition().value().x, position.value().x);
    ASSERT_FLOAT_EQ(sut->getPosition().value().y, position.value().y);
}

TEST_F(MainMenuButtonTest, buttonStateWillRemainIdleWhenMousePosDoesNotIntersectWithBackground)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    const auto omittingPosition = static_cast<sf::Vector2i>(position.toPixels() - sf::Vector2f(20.f, 20.f));
    sut->update(omittingPosition);
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_IDLE_COLORS.background);
}

TEST_F(MainMenuButtonTest, buttonStateWillChangeToHoverWhenMousePosIntersectsWithBackground)
{
    std::unique_ptr<NiceMock<Events::MouseEventListenerMock>> EventListener = std::make_unique<NiceMock<Events::MouseEventListenerMock>>();
    EXPECT_CALL(*EventListener, isLeftPressed()).WillOnce(Return(false));
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(EventListener));
    const auto intersectingPosition = static_cast<sf::Vector2i>(position.toPixels() + sf::Vector2f(10.f, 10.f));
    sut->update(intersectingPosition);
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_HOVER_COLORS.background);
}

TEST_F(MainMenuButtonTest, buttonStateWillChangeToActiveWhenMousePosIntersectsWithBackgroundAndisLeftPressed)
{
    std::unique_ptr<NiceMock<Events::MouseEventListenerMock>> EventListener = std::make_unique<NiceMock<Events::MouseEventListenerMock>>();
    EXPECT_CALL(*EventListener, isLeftPressed()).WillOnce(Return(true));
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::move(EventListener));
    const auto intersectingPosition = static_cast<sf::Vector2i>(position.toPixels() + sf::Vector2f(10.f, 10.f));
    sut->update(intersectingPosition);
    ASSERT_EQ(sut->getBackground().getFillColor(), TEST_ACTIVE_COLORS.background);
    ASSERT_TRUE(sut->isPressed());
}

TEST_F(MainMenuButtonTest, clonedButtonWillHaveTheSamePropertiesAsOriginalExceptNameAndPosition)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    auto result = sut->clone(sf::Text("clonedButton", sf::Font{}), VectorMath::ScreenPercentagePoint(sf::VideoMode(480, 480), sf::Vector2f(100, 100)));
    ASSERT_NE(result->getTextContent(), std::nullopt);
    ASSERT_EQ(result->getTextContent()->getString().toAnsiString(), "clonedButton");
    ASSERT_EQ(result->getPosition().value(), sf::Vector2f(100, 100));
    ASSERT_EQ(result->getSize().value(), size.value());
}

TEST_F(MainMenuButtonTest, clonedButtonWillHaveNulloptTextWhenNoneWasGiven)
{
    std::unique_ptr<Button> sut = std::make_unique<MainMenuButton>(
        position,
        size,
        sf::Text(name, sf::Font{}, characterSize),
        TEST_IDLE_COLORS,
        TEST_HOVER_COLORS,
        TEST_ACTIVE_COLORS,
        std::make_unique<NiceMock<Events::MouseEventListenerMock>>());
    auto result = sut->clone(std::nullopt, VectorMath::ScreenPercentagePoint(sf::VideoMode(480, 480), sf::Vector2f(100, 100)));
    ASSERT_EQ(result->getTextContent(), std::nullopt);
    ASSERT_EQ(result->getFont(), std::nullopt);
}

}