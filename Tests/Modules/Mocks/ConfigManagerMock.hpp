#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ConfigManager.hpp>

namespace Core
{

using ::testing::Test;

class ConfigManagerMock : public IConfigManager
{
public:
    MOCK_METHOD(void, setGraphics, (const FileMgmt::GraphicsConfig&), (override));
    MOCK_METHOD((const FileMgmt::GraphicsConfig&), getGraphics, (), (const, override));
    MOCK_METHOD((const FileMgmt::KeyboardConfig&), getKeyboard, (), (const, override));
};

}