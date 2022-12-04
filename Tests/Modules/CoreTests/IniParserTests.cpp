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
    IniParserTest()
    {
        IniParser::setBuildPath(TEST_PATH);
        sut = std::make_unique<IniParser>();
    }
    GraphicsConfig graphicsConfig;
    SupportedKeys supportedKeys;
    MainMenuKeys mainMenuKeys;
    std::unique_ptr<IIniParser> sut;
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
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut->parseFileTo(graphicsConfig), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsSupportedKeysConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(supportedKeys));
    ASSERT_EQ(supportedKeys.getKeys().at("Escape"), 36);
    ASSERT_EQ(supportedKeys.getKeys().at("D"), 3);
    ASSERT_EQ(supportedKeys.getKeys().at("PageDown"), 62);
}

TEST_F(IniParserTest, iniParserThrowsWhenSupportedKeysConfigFilePathIsInvalid)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut->parseFileTo(supportedKeys), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsMainMenuKeysWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(sut->parseFileTo(supportedKeys));
    ASSERT_NO_THROW(sut->parseFileTo(mainMenuKeys, supportedKeys));
    ASSERT_EQ(mainMenuKeys.getKeys().at("CLOSE"), 36);
}

TEST_F(IniParserTest, iniParserThrowsWhenMainMenuKeysFilePathIsInvalid)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut->parseFileTo(mainMenuKeys, supportedKeys), std::runtime_error);
}

}