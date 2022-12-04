#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <State.h>
#include <Config.h>
#include "AssetsManagerMock.h"

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
    }
    sf::Texture texture;
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

}