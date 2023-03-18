#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CoreBuilder.hpp>

namespace Core
{

using ::testing::Test;

class CoreBuilderMock : public CoreBuilder
{
public:
    MOCK_METHOD(std::unique_ptr<::Types::Window>, createWindow, (), (const, override));
    MOCK_METHOD(std::unique_ptr<Clock>, createClock, (), (const, override));
    MOCK_METHOD(std::unique_ptr<StateMachine>, createStateMachine, (), (const, override));
};

}