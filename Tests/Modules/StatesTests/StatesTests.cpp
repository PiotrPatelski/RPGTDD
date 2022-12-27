#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.h>
#include <ConfigManager.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.h"
#include "GuiManagerMock.hpp"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::ByMove;
using ::testing::_;

struct MainMenuStateTest : public testing::Test
{
    MainMenuStateTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        texture = std::make_shared<sf::Texture>();
        font = std::make_shared<sf::Font>();
        configManager = std::make_shared<Core::ConfigManager>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::MainMenuAssetsManagerMock>>();
        guiManager = std::make_unique<NiceMock<Gui::MainMenuGuiManagerMock>>();
        ON_CALL(*assetsManager, getTexture()).WillByDefault(Return(texture));
        ON_CALL(*assetsManager, getFont()).WillByDefault(Return(font));
    }
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<Core::ConfigManager> configManager;
    std::unique_ptr<NiceMock<FileMgmt::MainMenuAssetsManagerMock>> assetsManager;
    std::unique_ptr<NiceMock<Gui::MainMenuGuiManagerMock>> guiManager;
};

TEST_F(MainMenuStateTest, stateIsDoneWhenSetAsDone)
{
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut->markAsDone();
    ASSERT_TRUE(sut->isDone());
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundSizeProperly)
{
    FileMgmt::GraphicsConfig gfxConfig;
    gfxConfig.resolution = sf::VideoMode{480,480};
    configManager->setGraphics(gfxConfig);

    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*assetsManager, getTexture()).WillOnce(Return(std::make_shared<sf::Texture>()));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesFontProperly)
{
    font->loadFromFile(std::string(TEST_PATH) + "/Assets/Fonts/MainMenu/xbones.ttf");
    EXPECT_CALL(*assetsManager, getFont()).WillOnce(Return(font));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    ASSERT_EQ(sut->getFont()->getInfo().family, "xBONES");
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesKeybindsProperly)
{
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    ASSERT_EQ(configManager->getKeyboard().mainMenuKeys.getKeys().at("CLOSE"), 36);
}

TEST_F(MainMenuStateTest, mainMenuStateOutputsInitializedButtonBackgroundProperly)
{
    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["TEST"] = Gui::MainMenuButtonBuilder(sf::VideoMode(100, 100))
        .atPosition(2.f, 1.f).withSize(3.f, 7.f).build();

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));

    const auto buttonToDraw = sut->generateOutput().buttons[0];
    ASSERT_EQ(buttonToDraw.getPosition(), sf::Vector2f(2.f, 1.f));
    ASSERT_EQ(buttonToDraw.getSize(), sf::Vector2f(3.f, 7.f));
    ASSERT_EQ(buttonToDraw.getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttonToDraw.getOutlineColor(), sf::Color::Transparent);
}

TEST_F(MainMenuStateTest, mainMenuStateOutputsInitializedButtonTextProperly)
{
    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["TEST"] = Gui::MainMenuButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("test").build();

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));

    const auto buttonTextToDraw = sut->generateOutput().buttonTexts[0];
    ASSERT_EQ(buttonTextToDraw.getString(), "test");
    ASSERT_EQ(buttonTextToDraw.getFillColor(), sf::Color(70, 70, 70, 200));
}

}