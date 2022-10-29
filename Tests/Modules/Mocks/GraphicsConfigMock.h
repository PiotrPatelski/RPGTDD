#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GraphicsConfig.h>

namespace Core
{

using ::testing::Test;

class GraphicsConfigMock : public IGraphicsConfig
{
public:
    MOCK_METHOD(void, fetchSettingsFromFile, (IIniParser&), (override));
    MOCK_METHOD(bool, getFullscreen, (), (override));
    MOCK_METHOD(bool, getVerticalSync, (), (override));
    MOCK_METHOD(uint, getFrameRateLimit, (), (override));
    MOCK_METHOD(uint, getAntialiasingLevel, (), (override));
    MOCK_METHOD(sf::VideoMode, getResolution, (), (override));
};

}