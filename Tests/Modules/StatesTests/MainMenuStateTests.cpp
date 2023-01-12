#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.hpp"
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

struct MainMenuStateTest : public testing::Test
{
    MainMenuStateTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        texture = std::make_shared<sf::Texture>();
        font = std::make_shared<sf::Font>();
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        mainMenuAssetsManager = std::make_unique<NiceMock<FileMgmt::MainMenuAssetsManagerMock>>();
        mainMenuGuiManager = std::make_unique<NiceMock<Gui::MainMenuGuiManagerMock>>();
        mainMenuInputHandler = std::make_unique<NiceMock<Events::MainMenuInputHandlerMock>>();
        ON_CALL(*mainMenuAssetsManager, getTexture()).WillByDefault(Return(texture));
        ON_CALL(*mainMenuAssetsManager, getFont()).WillByDefault(Return(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(Return(dummyConfig));
    }
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::MainMenuAssetsManagerMock>> mainMenuAssetsManager;
    std::unique_ptr<NiceMock<Gui::MainMenuGuiManagerMock>> mainMenuGuiManager;
    std::unique_ptr<NiceMock<Events::MainMenuInputHandlerMock>> mainMenuInputHandler;
    FileMgmt::GraphicsConfig dummyConfig;
};

TEST_F(MainMenuStateTest, stateIsDoneWhenInputHandlerIsReadyToChange)
{
    EXPECT_CALL(*mainMenuInputHandler, isStateReadyToChange()).WillOnce(Return(true));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    ASSERT_TRUE(sut->isDone());
}

TEST_F(MainMenuStateTest, stateIsNotDoneWhenInputHandlerIsNotReadyToChange)
{
    EXPECT_CALL(*mainMenuInputHandler, isStateReadyToChange()).WillOnce(Return(false));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    ASSERT_FALSE(sut->isDone());
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundSizeProperly)
{
    FileMgmt::GraphicsConfig gfxConfig;
    gfxConfig.resolution = sf::VideoMode{480,480};
    configManager->setGraphics(gfxConfig);

    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*mainMenuAssetsManager, getTexture()).WillOnce(Return(std::make_shared<sf::Texture>()));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(MainMenuStateTest, mainMenuStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<Core::WindowMock>>();
    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton1").build()});
    buttons.push_back(Gui::StateChangingButton{Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton2").build()});
    buttons.push_back(Gui::StateChangingButton{Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton3").build()});
    buttons.push_back(Gui::StateChangingButton{Gui::ButtonBuilder(sf::VideoMode(100, 100)).
        withTextContent("testButton4").build()});

    EXPECT_CALL(*mainMenuGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    EXPECT_CALL(*window, draw(_)).Times(9);
    sut->drawOutput(*window);
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsGameStateWhenGameStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));

    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{std::move(gameButton)});

    std::unique_ptr<NiceMock<FileMgmt::GameAssetsManagerMock>> gameAssetsManager;
    std::unique_ptr<NiceMock<Gui::GameGuiManagerMock>> gameGuiManager;
    std::unique_ptr<NiceMock<Events::GameInputHandlerMock>> gameInputHandler;

    auto nextState = std::make_unique<GameState>(
        configManager,
        std::move(gameAssetsManager),
        std::move(gameGuiManager),
        std::move(gameInputHandler));

    EXPECT_CALL(*mainMenuGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    EXPECT_CALL(*mainMenuInputHandler, getNextStateOnActiveButton(_)).WillOnce(Return(ByMove(std::move(nextState))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    sut->update(sf::Vector2i{0,0}, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(GameState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsSettingsStateWhenSettingsStateButtonIsPressed)
{
    auto settingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));

    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{std::move(settingsButton)});

    auto settingsAssetsManager = std::make_unique<NiceMock<FileMgmt::SettingsAssetsManagerMock>>();
    auto settingsGuiManager = std::make_unique<NiceMock<Gui::SettingsGuiManagerMock>>();
    auto settingsInputHandler = std::make_unique<NiceMock<Events::SettingsInputHandlerMock>>();

    auto nextState = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(settingsInputHandler));

    EXPECT_CALL(*mainMenuGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    EXPECT_CALL(*mainMenuInputHandler, getNextStateOnActiveButton(_)).WillOnce(Return(ByMove(std::move(nextState))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    sut->update(sf::Vector2i{0,0}, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(SettingsState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsEditorStateWhenEditorStateButtonIsPressed)
{
    auto editorButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(editorButton), update(_));

    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{std::move(editorButton)});

    std::unique_ptr<NiceMock<FileMgmt::EditorAssetsManagerMock>> editorAssetsManager;
    std::unique_ptr<NiceMock<Gui::EditorGuiManagerMock>> editorGuiManager;
    std::unique_ptr<NiceMock<Events::EditorInputHandlerMock>> editorInputHandler;

    auto nextState = std::make_unique<EditorState>(
        configManager,
        std::move(editorAssetsManager),
        std::move(editorGuiManager),
        std::move(editorInputHandler));

    EXPECT_CALL(*mainMenuGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    EXPECT_CALL(*mainMenuInputHandler, getNextStateOnActiveButton(_)).WillOnce(Return(ByMove(std::move(nextState))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    sut->update(sf::Vector2i{0,0}, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(EditorState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsEmptyStateWhenExitStateButtonIsPressed)
{
    auto exitButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(exitButton), update(_));

    std::vector<Gui::StateChangingButton> buttons;
    buttons.push_back(Gui::StateChangingButton{std::move(exitButton)});

    std::unique_ptr<IState> nextState = nullptr;

    EXPECT_CALL(*mainMenuGuiManager, createButtons(_)).WillOnce(Return(ByMove(std::move(buttons))));
    EXPECT_CALL(*mainMenuInputHandler, getNextStateOnActiveButton(_)).WillOnce(Return(ByMove(std::move(nextState))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager),
        std::move(mainMenuInputHandler));
    sut->update(sf::Vector2i{0,0}, 0.f);
    ASSERT_EQ(sut->getNextState(), nullptr);
}

}