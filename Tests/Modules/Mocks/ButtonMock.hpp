#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Gui
{

class ButtonMock : public Button
{
public:
    MOCK_METHOD(const bool, isPressed, (), (const, override));
    MOCK_METHOD(std::optional<sf::Text>, getTextContent, (), (const, override));
    MOCK_METHOD(sf::Vector2f, getPosition, (), (const, override));
    MOCK_METHOD(sf::Vector2f, getSize, (), (const, override));
    MOCK_METHOD(std::optional<sf::Font>, getFont, (), (const, override));
    MOCK_METHOD(sf::RectangleShape, getBackground, (), (const, override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
    MOCK_METHOD(std::unique_ptr<Button>, clone, (const std::optional<sf::Text>, const sf::Vector2f&), (override));
};

}