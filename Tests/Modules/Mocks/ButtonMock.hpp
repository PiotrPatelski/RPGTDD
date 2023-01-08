#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Gui
{

class ButtonMock : public IButton
{
public:
    //TODO MOVE METHOD TO SEPARATE INTERFACE
    MOCK_METHOD(Events::StateChangeAction, getAction, (), (const, override));
    //
    MOCK_METHOD(const bool, isPressed, (), (const, override));
    MOCK_METHOD(sf::Text, getTextContent, (), (const, override));
    MOCK_METHOD(sf::Vector2f, getPosition, (), (const, override));
    MOCK_METHOD(sf::Vector2f, getSize, (), (const, override));
    MOCK_METHOD(sf::Font, getFont, (), (const, override));
    MOCK_METHOD(sf::RectangleShape, getBackground, (), (const, override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
};

}