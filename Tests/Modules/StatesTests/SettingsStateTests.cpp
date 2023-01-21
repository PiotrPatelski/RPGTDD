#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SettingsState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.hpp"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using namespace ::testing;

struct SettingsStateTest : public testing::Test
{
    SettingsStateTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        texture = std::make_shared<sf::Texture>();
        font = std::make_shared<sf::Font>();;
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        settingsAssetsManager = std::make_unique<NiceMock<FileMgmt::SettingsAssetsManagerMock>>();
        settingsGuiManager = std::make_unique<NiceMock<Gui::SettingsGuiManagerMock>>();
        ON_CALL(*settingsAssetsManager, getTexture()).WillByDefault(Return(texture));
        ON_CALL(*settingsAssetsManager, getFont()).WillByDefault(Return(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(Return(dummyConfig));
    }
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::SettingsAssetsManagerMock>> settingsAssetsManager;
    std::unique_ptr<NiceMock<Gui::SettingsGuiManagerMock>> settingsGuiManager;
    FileMgmt::GraphicsConfig dummyConfig;
};

TEST_F(SettingsStateTest, stateIsDoneWhenIsReadyToChange)
{
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager));
    sut->finishState();
    ASSERT_TRUE(sut->isReadyToChange());
}

TEST_F(SettingsStateTest, stateIsNotDoneWhenIsNotReadyToChange)
{
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager));
    ASSERT_FALSE(sut->isReadyToChange());
}

TEST_F(SettingsStateTest, settingsStateInitializesBackgroundSizeProperly)
{
    FileMgmt::GraphicsConfig gfxConfig;
    gfxConfig.resolution = sf::VideoMode{480,480};
    configManager->setGraphics(gfxConfig);

    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(SettingsStateTest, settingsStateStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*settingsAssetsManager, getTexture()).WillOnce(Return(std::make_shared<sf::Texture>()));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(SettingsStateTest, settingsStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<Core::WindowMock>>();

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::UserInterface>();
    gui->addButton(std::move(Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton1").build()), Events::ToMainMenuState());

    EXPECT_CALL(*settingsGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager));
    EXPECT_CALL(*window, draw(A<const sf::Drawable&>())).Times(3);
    sut->drawOutput(*window);
}

}