#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <DropDownList.hpp>

namespace Gui
{

using ::testing::Test;

class DropDownListMock : public DropDownList
{
public:
    MOCK_METHOD((const bool), isActive, (), (const, override));
    MOCK_METHOD(std::optional<Events::StateAction>, getActiveAction, (), (override));
    MOCK_METHOD((const sf::Text), getTextContent, (), (const, override));
    MOCK_METHOD(void, addSection, (const std::string&, Events::StateAction), (override));
    MOCK_METHOD(void, update, (const sf::Vector2i&), (override));
    MOCK_METHOD(void, drawTo, (Core::IWindow&), (override));
};

}