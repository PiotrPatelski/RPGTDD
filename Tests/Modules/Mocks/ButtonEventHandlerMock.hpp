#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonEventHandler.hpp>

namespace Events
{

using ::testing::Test;

class ButtonEventHandlerMock : public IButtonEventHandler
{
public:
   MOCK_METHOD(bool, isPressed, (), (const, override));
};

}