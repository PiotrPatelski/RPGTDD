#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EngineContext.h>

namespace Core
{

using ::testing::Test;

class EngineContextMock : public IEngineContext
{
public:
    MOCK_METHOD(IWindow&, getWindow, (), (override));
    MOCK_METHOD(IClock&, getClock, (), (override));
    MOCK_METHOD(IStateMachine&, getStateMachine, (), (override));
};

}