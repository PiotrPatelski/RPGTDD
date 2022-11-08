#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IniParser.h>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace Core
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;

struct IniParserTest : public testing::Test
{
    const std::string pathToFile = TEST_PATH;
    GraphicsConfig graphicsConfig;
    KeyboardConfig keyboardConfig;
    std::unique_ptr<IIniParser> sut = std::make_unique<IniParser>(pathToFile);
};

TEST_F(IniParserTest, iniParserFillsGraphicsConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(graphicsConfig));
    ASSERT_EQ(graphicsConfig.gameTitle, "TESTCONFIG");
    ASSERT_EQ(graphicsConfig.resolution.width, 21);
    ASSERT_EQ(graphicsConfig.resolution.height, 37);
    ASSERT_TRUE(graphicsConfig.fullscreen);
    ASSERT_EQ(graphicsConfig.frameRateLimit, 30);
    ASSERT_TRUE(graphicsConfig.verticalSync);
    ASSERT_EQ(graphicsConfig.contextSettings.antialiasingLevel, 1);
}

TEST_F(IniParserTest, iniParserThrowsWhenGraphicsConfigFilePathIsInvalid)
{
    const std::string invalidPath = "invalid";
    sut.reset(new IniParser(invalidPath));
    ASSERT_THROW(sut->parseFileTo(graphicsConfig), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsKeyboardConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(keyboardConfig));
    ASSERT_EQ(keyboardConfig.supportedKeys.at("Escape"), 36);
    ASSERT_EQ(keyboardConfig.supportedKeys.at("D"), 3);
    ASSERT_EQ(keyboardConfig.supportedKeys.at("PageDown"), 62);
}

TEST_F(IniParserTest, iniParserThrowsWhenKeyboardConfigFilePathIsInvalid)
{
    const std::string invalidPath = "invalid";
    sut.reset(new IniParser(invalidPath));
    ASSERT_THROW(sut->parseFileTo(keyboardConfig), std::runtime_error);
}

}