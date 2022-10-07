#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Clock.h>

namespace Core
{

using ::testing::Test;

class ClockMock : public IClock
{
public:
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(float, getDeltaTime, (), (override));
};

}