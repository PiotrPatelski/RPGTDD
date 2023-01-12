#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <CoreBuilder.hpp>

namespace Core
{

using ::testing::Test;

class CoreBuilderMock : public ICoreBuilder
{
public:
    MOCK_METHOD(std::unique_ptr<IWindow>, createWindow, (), (const, override));
    MOCK_METHOD(std::unique_ptr<IClock>, createClock, (), (const, override));
    MOCK_METHOD(std::unique_ptr<IStateMachine>, createStateMachine, (), (const, override));
};

}