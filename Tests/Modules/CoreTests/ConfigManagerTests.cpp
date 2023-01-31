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
};

TEST_F(ConfigManagerTest, configIsModifiedWithDiffOnlyAfterApplyCall)
{
    auto requestedResolution = sf::VideoMode(480, 480);
    auto request = [requestedResolution](FileMgmt::GraphicsConfig& config)
        {config.resolution = requestedResolution;};
    sut->queueGraphicsRequest(request);
    ASSERT_NE(sut->getGraphics().resolution, requestedResolution);
    sut->applyDiff();
    ASSERT_EQ(sut->getGraphics().resolution, requestedResolution);
}

}