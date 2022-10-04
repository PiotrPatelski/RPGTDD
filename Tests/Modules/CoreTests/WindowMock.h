#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Core
{

using ::testing::Test;

class WindowMock : public IWindow
{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, displayWindow, (), (override));
};



}