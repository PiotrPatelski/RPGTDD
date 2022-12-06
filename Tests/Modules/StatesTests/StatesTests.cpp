#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.h>
#include <Config.h>
#include "AssetsManagerMock.h"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;

struct MainMenuStateTest : public testing::Test
{
    MainMenuStateTest()
    {
        assetsManager = std::make_unique<NiceMock<Core::MainMenuAssetsManagerMock>>();
        ON_CALL(*assetsManager, getTexture()).WillByDefault(ReturnRef(texture));
        ON_CALL(*assetsManager, getFont()).WillByDefault(ReturnRef(font));
    }
    sf::Texture texture;
    sf::Font font;
    Core::GraphicsConfig graphicsConfig;
    Core::KeyboardConfig keyboardConfig;
    std::unique_ptr<NiceMock<Core::MainMenuAssetsManagerMock>> assetsManager;
};

TEST_F(MainMenuStateTest, stateIsDoneWhenSetAsDone)
{
    auto sut = std::make_unique<MainMenuState>(
        graphicsConfig,
        keyboardConfig,
        std::move(assetsManager));
    sut->markAsDone();
    ASSERT_TRUE(sut->isDone());
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundSizeProperly)
{
    graphicsConfig.resolution = sf::VideoMode{480,480};
    auto sut = std::make_unique<MainMenuState>(
        graphicsConfig,
        keyboardConfig,
        std::move(assetsManager));
    ASSERT_EQ(sut->getBackground().getSize().x, 480);
    ASSERT_EQ(sut->getBackground().getSize().y, 480);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*assetsManager, fetchTextureFromFile());
    auto sut = std::make_unique<MainMenuState>(
        graphicsConfig,
        keyboardConfig,
        std::move(assetsManager));
    ASSERT_NE(sut->getBackground().getTexture(), nullptr);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesFontProperly)
{
    sf::Font font;
    font.loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    EXPECT_CALL(*assetsManager, fetchFontFromFile());
    EXPECT_CALL(*assetsManager, getFont()).WillOnce(ReturnRef(font));
    auto sut = std::make_unique<MainMenuState>(
        graphicsConfig,
        keyboardConfig,
        std::move(assetsManager));
    ASSERT_EQ(sut->getFont().getInfo().family, "xBONES");
}

}