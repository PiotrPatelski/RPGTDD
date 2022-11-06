#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Engine.h>

namespace Core
{

using ::testing::Test;

class EngineContextMock : public Engine
{
public:
    MOCK_METHOD(IClock&, getClock, (), (override));
    MOCK_METHOD(GraphicsConfig&, getGraphicsConfig, (), (override));
    MOCK_METHOD(KeyboardConfig&, getKeyboardConfig, (), (override));
    MOCK_METHOD(bool, updateState, (), (override));
    MOCK_METHOD(bool, isWindowOpen, (), (override));
    MOCK_METHOD(void, closeWindow, (), (override));
    MOCK_METHOD(void, displayRenderedFrame, (), (override));
    MOCK_METHOD(void, launchWindow, (), (override));
    MOCK_METHOD(void, runInitialState, (), (override));
};

}