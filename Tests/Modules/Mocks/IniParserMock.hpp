#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Config.hpp>

namespace FileMgmt
{

using ::testing::Test;

class IniParserMock : public IIniParser
{
public:
    MOCK_METHOD(GraphicsConfig, getGraphicsConfig, (), (override));
    MOCK_METHOD(std::unique_ptr<KeyMap>, getKeyboardConfig, (), (override));
    MOCK_METHOD(std::unique_ptr<KeyMap>, getMainMenuKeys, (const KeyMap&), (override));
    MOCK_METHOD(std::unique_ptr<KeyMap>, getEditorKeys, (const KeyMap&), (override));
    MOCK_METHOD(void, setGraphicsConfig, (const GraphicsConfig&), (override));
};

}