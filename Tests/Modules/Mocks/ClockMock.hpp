#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Clock.hpp>

namespace Core
{

using ::testing::Test;

class ClockMock : public Clock
{
public:
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(const float, getDeltaTime, (), (const, override));
};

}