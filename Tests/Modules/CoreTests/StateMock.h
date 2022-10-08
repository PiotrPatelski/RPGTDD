#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <State.h>

namespace States
{

using ::testing::Test;
using testing::Return;

class StateMock : public IState
{
public:
    MOCK_METHOD(void, changeState, (), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(bool, isDone, (), (override));
    MOCK_METHOD(void, markAsDone, (), (override));

};

}