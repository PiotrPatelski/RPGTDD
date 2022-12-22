#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Config.h>

namespace Core
{

using ::testing::Test;

class IniParserMock : public IIniParser
{
public:
    MOCK_METHOD(std::ifstream, findAndOpenFile, (const std::string&), (override));
    MOCK_METHOD(GraphicsConfig, parseGraphicsConfig, (), (override));
    MOCK_METHOD(SupportedKeys, parseKeyboardConfig, (), (override));
    MOCK_METHOD(MainMenuKeys, parseMainMenuKeys, (const SupportedKeys&), (override));
};

}