#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.h"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"

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
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::MainMenuAssetsManagerMock>>();
        guiManager = std::make_unique<NiceMock<Gui::MainMenuGuiManagerMock>>();
        ON_CALL(*assetsManager, getTexture()).WillByDefault(Return(texture));
        ON_CALL(*assetsManager, getFont()).WillByDefault(Return(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(Return(dummyConfig));
    }
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::MainMenuAssetsManagerMock>> assetsManager;
    std::unique_ptr<NiceMock<Gui::MainMenuGuiManagerMock>> guiManager;
    FileMgmt::GraphicsConfig dummyConfig;
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

TEST_F(MainMenuStateTest, mainMenuStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<Core::WindowMock>>();
    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["TEST_BUTTON1"] = Gui::MainMenuButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton1").build();
    buttons["TEST_BUTTON2"] = Gui::MainMenuButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton2").build();

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    EXPECT_CALL(*window, draw(_)).Times(5);
    sut->drawOutput(*window);
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsGameStateWhenGameStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(true));

    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["GAME_STATE"] = std::move(gameButton);

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut->update(sf::Vector2i{0,0}, 0.f);
    ASSERT_TRUE(sut->isDone());
    auto nextState = sut->getNextState();
    EXPECT_NE(nextState, nullptr);
    EXPECT_EQ(typeid(GameState), typeid(*nextState));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsSettingsStateWhenSettingsStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(false));
    auto settingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));
    EXPECT_CALL(*(settingsButton), isPressed()).WillOnce(Return(true));

    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["GAME_STATE"] = std::move(gameButton);
    buttons["SETTINGS_STATE"] = std::move(settingsButton);

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut->update(sf::Vector2i{0,0}, 0.f);
    ASSERT_TRUE(sut->isDone());
    auto nextState = sut->getNextState();
    EXPECT_NE(nextState, nullptr);
    EXPECT_EQ(typeid(SettingsState), typeid(*nextState));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsEditorStateWhenEditorStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(false));
    auto settingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));
    EXPECT_CALL(*(settingsButton), isPressed()).WillOnce(Return(false));
    auto editorButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(editorButton), update(_));
    EXPECT_CALL(*(editorButton), isPressed()).WillOnce(Return(true));

    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["GAME_STATE"] = std::move(gameButton);
    buttons["SETTINGS_STATE"] = std::move(settingsButton);
    buttons["EDITOR_STATE"] = std::move(editorButton);

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut->update(sf::Vector2i{0,0}, 0.f);
    ASSERT_TRUE(sut->isDone());
    auto nextState = sut->getNextState();
    EXPECT_NE(nextState, nullptr);
    EXPECT_EQ(typeid(EditorState), typeid(*nextState));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsEmptyStateWhenExitStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(false));
    auto settingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));
    EXPECT_CALL(*(settingsButton), isPressed()).WillOnce(Return(false));
    auto editorButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(editorButton), update(_));
    EXPECT_CALL(*(editorButton), isPressed()).WillOnce(Return(false));
    auto exitButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(exitButton), update(_));
    EXPECT_CALL(*(exitButton), isPressed()).WillOnce(Return(true));

    std::map<std::string, std::unique_ptr<Gui::IButton>> buttons;
    buttons["GAME_STATE"] = std::move(gameButton);
    buttons["SETTINGS_STATE"] = std::move(settingsButton);
    buttons["EDITOR_STATE"] = std::move(editorButton);
    buttons["EXIT_STATE"] = std::move(exitButton);

    EXPECT_CALL(*guiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut->update(sf::Vector2i{0,0}, 0.f);
    ASSERT_TRUE(sut->isDone());
    ASSERT_EQ(sut->getNextState(), nullptr);
}

}