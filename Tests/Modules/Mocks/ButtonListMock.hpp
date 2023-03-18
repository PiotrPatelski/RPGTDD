#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonList.hpp>

namespace Gui
{

using ::testing::Test;

class ButtonListMock : public ButtonList
{
public:
    ButtonListMock()
    : ButtonList(sf::Text{}){}
    MOCK_METHOD((bool), isActive, (), (const, override));
    MOCK_METHOD(std::optional<Events::StateAction>, getActiveAction, (), (override));
    MOCK_METHOD((sf::Text), getTextContent, (), (const, override));
    MOCK_METHOD((VectorMath::ScreenPercentagePoint), getPosition, (), (const, override));
    MOCK_METHOD((VectorMath::ScreenPercentagePoint), getSize, (), (const, override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
    MOCK_METHOD(void, drawTo, (Types::Window&), (override));
};

}