#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Gui
{

class ButtonMock : public IButton
{
public:
    MOCK_METHOD(sf::Text, getTextContent, (), (override));
    MOCK_METHOD(sf::Vector2f, getPosition, (), (override));
    MOCK_METHOD(sf::Vector2f, getSize, (), (override));
    MOCK_METHOD(sf::Font, getFont, (), (override));
    MOCK_METHOD(sf::RectangleShape, getBackground, (), (override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
};

}