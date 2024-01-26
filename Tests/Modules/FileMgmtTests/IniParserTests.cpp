#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IniParser.hpp>

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace FileMgmt
{

using ::testing::NiceMock;
using ::testing::Test;
using ::testing::Return;

struct IniParserTest : public testing::Test
{
    IniParserTest()
    {
        IniParser::setBuildPath(TEST_PATH);
        resetToDefaultConfig();
    }

    GraphicsConfig graphicsConfig;
    std::unique_ptr<KeyMap> supportedKeys;
    std::unique_ptr<KeyMap> mainMenuKeys;
    IniParser sut;
    void resetToDefaultConfig()
    {
        IniParser::setBuildPath(TEST_PATH);
        sf::ContextSettings ctxSettings;
        ctxSettings.antialiasingLevel = 1;
        GraphicsConfig defaultTestConfig
        {
            "TESTCONFIG",
            sf::VideoMode(21, 37),
            true,
            30,
            true,
            ctxSettings
        };
        sut.overwriteGraphicsConfig(defaultTestConfig);
    }

};

TEST_F(IniParserTest, iniParserFillsGraphicsConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(graphicsConfig = sut.getGraphicsConfig());
    ASSERT_EQ(graphicsConfig.gameTitle, "TESTCONFIG");
    ASSERT_EQ(graphicsConfig.resolution.width, 21);
    ASSERT_EQ(graphicsConfig.resolution.height, 37);
    ASSERT_TRUE(graphicsConfig.fullscreen);
    ASSERT_EQ(graphicsConfig.frameRateLimit, 30);
    ASSERT_TRUE(graphicsConfig.verticalSync);
    ASSERT_EQ(graphicsConfig.contextSettings.antialiasingLevel, 1);
}

TEST_F(IniParserTest, iniParserThrowsWhenGraphicsConfigFilePathIsInvalidOnRead)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut.getGraphicsConfig(), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsSupportedKeysConfigWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(supportedKeys = sut.getKeyboardConfig());
    ASSERT_EQ(supportedKeys->getKey("Escape"), 36);
    ASSERT_EQ(supportedKeys->getKey("D"), 3);
    ASSERT_EQ(supportedKeys->getKey("PageDown"), 62);
}

TEST_F(IniParserTest, iniParserThrowsWhenSupportedKeysConfigFilePathIsInvalid)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut.getKeyboardConfig(), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsMainMenuKeysWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(supportedKeys = sut.getKeyboardConfig());
    ASSERT_NO_THROW(mainMenuKeys = sut.getMainMenuKeys(*supportedKeys));
    ASSERT_EQ(mainMenuKeys->getKey("CLOSE"), 36);
}

TEST_F(IniParserTest, iniParserThrowsWhenMainMenuKeysFilePathIsInvalid)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut.getMainMenuKeys(*supportedKeys), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsEditorKeysWithDataParsedFromTestConfigFile)
{
    ASSERT_NO_THROW(supportedKeys = sut.getKeyboardConfig());
    ASSERT_NO_THROW(mainMenuKeys = sut.getEditorKeys(*supportedKeys));
    ASSERT_EQ(mainMenuKeys->getKey("PAUSE"), 36);
}

TEST_F(IniParserTest, iniParserThrowsWhenEditorKeysFilePathIsInvalid)
{
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut.getEditorKeys(*supportedKeys), std::runtime_error);
}

TEST_F(IniParserTest, iniParserOverwritesGraphicsIniWithNoThrow)
{
    GraphicsConfig configToOverwrite
    {
        "overwrite",
        sf::VideoMode(480, 480),
        false,
        40,
        false,
        sf::ContextSettings()
    };
    ASSERT_NO_THROW(sut.overwriteGraphicsConfig(configToOverwrite));
    ASSERT_NO_THROW(graphicsConfig = sut.getGraphicsConfig());
    ASSERT_EQ(graphicsConfig.gameTitle, configToOverwrite.gameTitle);
    ASSERT_EQ(graphicsConfig.resolution.width, configToOverwrite.resolution.width);
    ASSERT_EQ(graphicsConfig.resolution.height, configToOverwrite.resolution.height);
    ASSERT_FALSE(graphicsConfig.fullscreen);
    ASSERT_EQ(graphicsConfig.frameRateLimit, configToOverwrite.frameRateLimit);
    ASSERT_FALSE(graphicsConfig.verticalSync);
    ASSERT_EQ(graphicsConfig.contextSettings.antialiasingLevel, 0);
}

TEST_F(IniParserTest, iniParserThrowsWhenGraphicsFilePathIsInvalidOnWrite)
{
    GraphicsConfig configToOverwrite;
    IniParser::setBuildPath("invalidPath");
    ASSERT_THROW(sut.overwriteGraphicsConfig(configToOverwrite), std::runtime_error);
}

TEST_F(IniParserTest, iniParserFillsTileIdConfigWithDataParsedFromTestConfigFile)
{
    std::vector<std::string> tileIdConfig;
    ASSERT_NO_THROW(tileIdConfig = sut.getTileIdConfig());
    ASSERT_EQ(tileIdConfig[0], "TILE1");
    ASSERT_EQ(tileIdConfig[1], "TILE2");
    ASSERT_EQ(tileIdConfig[2], "TILE3");
    ASSERT_EQ(tileIdConfig[3], "TILE4");
}


}