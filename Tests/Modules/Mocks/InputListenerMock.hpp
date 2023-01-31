#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputListener.hpp>

namespace Events
{

using ::testing::Test;

class InputListenerMock : public IInputListener
{
public:
    MOCK_METHOD(std::optional<Events::StateAction>, getActiveAction, (), (const, override));
};

}