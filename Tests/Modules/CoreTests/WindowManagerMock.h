#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Core
{

using ::testing::Test;

class WindowManagerMock : public IWindowManager
{
public:
    MOCK_METHOD(bool, isWindowActive, (), (override));
};



}