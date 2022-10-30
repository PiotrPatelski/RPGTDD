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
    MOCK_METHOD(bool, getFullscreen, (), (const, override));
    MOCK_METHOD(bool, getVerticalSync, (), (const, override));
    MOCK_METHOD(uint, getFrameRateLimit, (), (const, override));
    MOCK_METHOD(std::string, getGameTitle, (), (const, override));
    MOCK_METHOD(sf::ContextSettings, getContextSettings, (), (const, override));
    MOCK_METHOD(sf::VideoMode, getResolution, (), (const, override));
};

}