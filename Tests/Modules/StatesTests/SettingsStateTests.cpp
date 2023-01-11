#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SettingsState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.h"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"
#include "InputHandlerMock.hpp"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::ByMove;
using ::testing::_;

struct SettingsStateTest : public testing::Test
{
    SettingsStateTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        texture = std::make_shared<sf::Texture>();
        font = std::make_shared<sf::Font>();
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        settingsAssetsManager = std::make_unique<NiceMock<FileMgmt::SettingsAssetsManagerMock>>();
        settingsGuiManager = std::make_unique<NiceMock<Gui::SettingsGuiManagerMock>>();
        settingsInputHandler = std::make_unique<NiceMock<Events::SettingsInputHandlerMock>>();
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
    std::unique_ptr<NiceMock<Events::SettingsInputHandlerMock>> settingsInputHandler;
    FileMgmt::GraphicsConfig dummyConfig;
};

TEST_F(SettingsStateTest, stateIsDoneWhenInputHandlerIsReadyToChange)
{
    EXPECT_CALL(*settingsInputHandler, isStateReadyToChange()).WillOnce(Return(true));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));
    ASSERT_TRUE(sut->isDone());
}

TEST_F(SettingsStateTest, stateIsNotDoneWhenInputHandlerIsNotReadyToChange)
{
    EXPECT_CALL(*settingsInputHandler, isStateReadyToChange()).WillOnce(Return(false));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));
    ASSERT_FALSE(sut->isDone());
}

TEST_F(SettingsStateTest, settingsStateInitializesBackgroundSizeProperly)
{
    FileMgmt::GraphicsConfig gfxConfig;
    gfxConfig.resolution = sf::VideoMode{480,480};
    configManager->setGraphics(gfxConfig);

    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(SettingsStateTest, settingsStateStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*settingsAssetsManager, getTexture()).WillOnce(Return(std::make_shared<sf::Texture>()));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(SettingsStateTest, settingsStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<Core::WindowMock>>();
    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton1").build()});

    EXPECT_CALL(*settingsGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));
    EXPECT_CALL(*window, draw(_)).Times(3);
    sut->drawOutput(*window);
}

}