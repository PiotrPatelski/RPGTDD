#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ConfigManager.hpp>

namespace FileMgmt
{

using ::testing::Test;

class ConfigManagerMock : public IConfigManager
{
public:
    MOCK_METHOD(void, queueGraphicsRequest, (std::function<void(FileMgmt::GraphicsConfig&)>), (override));
    MOCK_METHOD(void, applyDiff, (), (override));
    MOCK_METHOD((const FileMgmt::GraphicsConfig&), getGraphics, (), (const, override));
    MOCK_METHOD((const FileMgmt::KeyboardConfig&), getKeyboard, (), (const, override));
    MOCK_METHOD((const std::vector<std::string>&), getTileIdConfig, (), (const, override));
};

}