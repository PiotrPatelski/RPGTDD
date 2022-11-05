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
    MOCK_METHOD(void, parseFileTo, (GraphicsConfig&), (override));
    MOCK_METHOD(void, parseFileTo, (KeyboardConfig&), (override));
};

}