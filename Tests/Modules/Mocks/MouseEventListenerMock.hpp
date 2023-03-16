#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MouseEventListener.hpp>

namespace Events
{

using ::testing::Test;

class MouseEventListenerMock : public MouseEventListener
{
public:
   MOCK_METHOD(bool, isLeftPressed, (), (const, override));
   MOCK_METHOD(bool, isRightPressed, (), (const, override));
};

}