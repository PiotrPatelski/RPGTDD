#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GraphicsConfig.h>

namespace Core
{

using ::testing::Test;

class IniParserMock : public IIniParser
{
public:
    MOCK_METHOD(GraphicsData, fetchDataFromGraphicsFile, (), (override));
};

}