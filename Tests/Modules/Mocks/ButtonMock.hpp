#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ScreenPercentagePoint.hpp>

namespace Gui
{

class ButtonMock : public Button
{
public:
    MOCK_METHOD(const bool, isPressed, (), (const, override));
    MOCK_METHOD(std::optional<sf::Text>, getTextContent, (), (const, override));
    MOCK_METHOD(void, setTextContent, (const sf::Text&), (override));
    MOCK_METHOD(VectorMath::ScreenPercentagePoint, getPosition, (), (const, override));
    MOCK_METHOD(VectorMath::ScreenPercentagePoint, getSize, (), (const, override));
    MOCK_METHOD(std::optional<sf::Font>, getFont, (), (const, override));
    MOCK_METHOD(::Types::Background, getBackground, (), (const, override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
    MOCK_METHOD(std::unique_ptr<Button>, clone, (const std::optional<sf::Text>, const VectorMath::ScreenPercentagePoint&), (override));
};

}