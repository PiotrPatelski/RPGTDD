#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <State.h>

namespace States
{

using ::testing::Test;
using testing::Return;

class StateMock : public State
{
public:
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(void, update, (float), (override));
    MOCK_METHOD(bool, isDone, (), (override));
    MOCK_METHOD(void, markAsDone, (), (override));

};

}