#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ConfigManager.hpp>

namespace Core
{

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

struct ConfigManagerTest : public testing::Test
{
    ConfigManagerTest()
    {
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        sut = std::make_unique<ConfigManager>();
    }
    std::unique_ptr<IConfigManager> sut;
    ~ConfigManagerTest()
    {
        void resetToDefaultConfig();
    }
    void resetToDefaultConfig()
    {
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        sf::ContextSettings ctxSettings;
        ctxSettings.antialiasingLevel = 1;
        FileMgmt::GraphicsConfig defaultTestConfig
        {
            "TESTCONFIG",
            sf::VideoMode(21, 37),
            true,
            30,
            true,
            ctxSettings
        };
        FileMgmt::IniParser parser;
        parser.setGraphicsConfig(defaultTestConfig);
    }
};

TEST_F(ConfigManagerTest, configIsModifiedWithDiffOnlyAfterApplyCall)
{
    auto requestedResolution = sf::VideoMode(480, 480);
    auto request = [requestedResolution](FileMgmt::GraphicsConfig& config)
        {config.resolution = requestedResolution;};
    sut->queueGraphicsRequest(request);
    ASSERT_NE(sut->getGraphics().resolution, requestedResolution);
    sut->applyDiff();
    sut = std::make_unique<ConfigManager>();
    ASSERT_EQ(sut->getGraphics().resolution.width, requestedResolution.width);
    ASSERT_EQ(sut->getGraphics().resolution.height, requestedResolution.height);
}

}