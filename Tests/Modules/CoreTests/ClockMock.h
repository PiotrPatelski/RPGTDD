#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Clock.h>

namespace Core
{

using ::testing::Test;
using ::testing::Return;
using ::testing::NiceMock;
using ::testing::ByMove;

class ClockMock : public IClock
{
public:
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(float, getDeltaTime, (), (override));
};

}