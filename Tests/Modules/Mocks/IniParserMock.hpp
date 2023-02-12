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
    MOCK_METHOD(SupportedKeys, getKeyboardConfig, (), (override));
    MOCK_METHOD(MainMenuKeys, getMainMenuKeys, (const SupportedKeys&), (override));
    MOCK_METHOD(void, setGraphicsConfig, (const GraphicsConfig&), (override));
};

}