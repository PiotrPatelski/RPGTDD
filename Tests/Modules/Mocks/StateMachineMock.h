#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StateMachine.h>


namespace Core
{

class StateMachineMock : public IStateMachine
{
public:
    MOCK_METHOD(void, update, (bool, float), (override));
    MOCK_METHOD(bool, isWorkDone, (), (override));
    MOCK_METHOD(void, runState, (std::unique_ptr<States::IState>), (override));
};

}