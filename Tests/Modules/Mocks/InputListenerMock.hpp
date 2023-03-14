#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputListener.hpp>

namespace Events
{

using ::testing::Test;

class InputListenerMock : public InputListener
{
public:
    MOCK_METHOD(std::optional<Events::StateAction>, getKeyboardAction, (), (const, override));
    MOCK_METHOD(std::optional<Events::StateAction>, getMouseAction, (const sf::Vector2i&), (const, override));
};

}