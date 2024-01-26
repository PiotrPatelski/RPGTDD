#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Engine.hpp>

namespace Core
{

using ::testing::Test;

class EngineMock : public IEngine
{
public:
    MOCK_METHOD(void, updateDeltaTime, (), (override));
    MOCK_METHOD(bool, updateState, (), (override));
    MOCK_METHOD(bool, isWindowOpen, (), (override));
    MOCK_METHOD(void, closeWindow, (), (override));
    MOCK_METHOD(void, displayRenderedFrame, (), (override));
    MOCK_METHOD(void, launchWindow, (const FileMgmt::GraphicsConfig&), (override));
    MOCK_METHOD(void, runInitialState, (std::shared_ptr<FileMgmt::IConfigManager>), (override));
};

}