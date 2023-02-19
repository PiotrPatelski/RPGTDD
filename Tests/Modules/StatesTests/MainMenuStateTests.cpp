#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <MenuGui.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include "AssetsManagerMock.hpp"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"
#include "ButtonBuilderMock.hpp"
#include "ButtonListBuilderMock.hpp"

#define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using namespace ::testing;

struct MainMenuStateTest : public testing::Test
{
    MainMenuStateTest()
    {
        FileMgmt::AssetsManager::setBuildPath(TEST_PATH);
        FileMgmt::IniParser::setBuildPath(TEST_PATH);
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        mainMenuAssetsManager = std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>();
        mainMenuGuiManager = std::make_unique<NiceMock<Gui::GuiManagerMock>>();
        ON_CALL(*mainMenuAssetsManager, getTexture(_)).WillByDefault(Return(&texture));
        ON_CALL(*mainMenuAssetsManager, getFont(_)).WillByDefault(ReturnRef(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(ReturnRef(dummyConfig));
        ON_CALL(*configManager, getKeyboard).WillByDefault(ReturnRef(keyboard));
    }
    sf::Texture texture;
    sf::Font font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::AssetsManagerMock>> mainMenuAssetsManager;
    std::unique_ptr<NiceMock<Gui::GuiManagerMock>> mainMenuGuiManager;
    NiceMock<::Types::WindowMock> window;
    FileMgmt::GraphicsConfig dummyConfig;
    FileMgmt::KeyboardConfig keyboard;
};

TEST_F(MainMenuStateTest, stateIsDoneWhenIsReadyToChange)
{
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    sut->finishState();
    ASSERT_TRUE(sut->isReadyToChange());
}

TEST_F(MainMenuStateTest, stateIsNotDoneWhenIsNotReadyToChange)
{
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    ASSERT_FALSE(sut->isReadyToChange());
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundSizeProperly)
{
    configManager->queueGraphicsRequest(
        [](FileMgmt::GraphicsConfig& gfxConfig)
        {
            gfxConfig.resolution = sf::VideoMode{480,480};
        });

    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundTextureProperly)
{
    const sf::Texture texture;
    EXPECT_CALL(*mainMenuAssetsManager, getTexture(Eq("MENU_BACKGROUND"))).WillOnce(Return(&texture));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(MainMenuStateTest, mainMenuStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    auto callback = [](States::MenuState&){};
    gui->addButton(Gui::MenuButtonBuilder().
            withTextContent(sf::Text("testButton1", font)).build(), callback);
    gui->addButton(Gui::MenuButtonBuilder().
            withTextContent(sf::Text("testButton2", font)).build(), callback);
    gui->addButton(Gui::MenuButtonBuilder().
            withTextContent(sf::Text("testButton3", font)).build(), callback);
    gui->addButton(Gui::MenuButtonBuilder().
            withTextContent(sf::Text("testButton4", font)).build(), callback);

    EXPECT_CALL(*mainMenuGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    EXPECT_CALL(*window, draw(A<const sf::Drawable&>())).Times(9);
    sut->drawOutput(*window);
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsGameStateWhenGameStateButtonIsPressed)
{
    auto gameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    gui->addButton(std::move(gameButton), Events::ToGameState());

    EXPECT_CALL(*mainMenuGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    EXPECT_CALL(window, getMousePosition());
    sut->update(window, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(GameState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsSettingsStateWhenSettingsStateButtonIsPressed)
{
    auto settingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));
    EXPECT_CALL(*(settingsButton), isPressed()).WillOnce(Return(true));

    FileMgmt::KeyboardConfig config;
    EXPECT_CALL(*configManager, getKeyboard()).WillOnce(ReturnRef(config));

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    gui->addButton(std::move(settingsButton), Events::ToSettingsState());

    EXPECT_CALL(*mainMenuGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    EXPECT_CALL(window, getMousePosition());
    sut->update(window, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(SettingsState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsEditorStateWhenEditorStateButtonIsPressed)
{
    auto editorButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(editorButton), update(_));
    EXPECT_CALL(*(editorButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    gui->addButton(std::move(editorButton), Events::ToEditorState());

    EXPECT_CALL(*mainMenuGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    EXPECT_CALL(window, getMousePosition());
    sut->update(window, 0.f);
    auto result = sut->getNextState();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(typeid(EditorState), typeid(*result));
}

TEST_F(MainMenuStateTest, mainMenuStateAssignsNullptrWhenExitStateButtonIsPressed)
{
    auto exitButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(exitButton), update(_));
    EXPECT_CALL(*(exitButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    gui->addButton(std::move(exitButton), Events::ToExitState());

    EXPECT_CALL(*mainMenuGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    EXPECT_CALL(window, getMousePosition());
    sut->update(window, 0.f);
    ASSERT_EQ(sut->getNextState(), nullptr);
}

struct MenuStateButtonActionsTest : public MainMenuStateTest
{
    MenuStateButtonActionsTest()
    {
        buttonBuilder = std::make_unique<NiceMock<Gui::ButtonBuilderMock>>();
        ON_CALL(*buttonBuilder, withTextContent(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, atPosition(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withSize(_)).WillByDefault(ReturnRef(*buttonBuilder));
        toGameButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
        toSettingsButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
        toEditorButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
        toExitButton = std::make_unique<NiceMock<Gui::ButtonMock>>();
    }
    std::unique_ptr<NiceMock<Gui::ButtonBuilderMock>> buttonBuilder;
    std::unique_ptr<NiceMock<Gui::ButtonMock>> toGameButton;
    std::unique_ptr<NiceMock<Gui::ButtonMock>> toSettingsButton;
    std::unique_ptr<NiceMock<Gui::ButtonMock>> toEditorButton;
    std::unique_ptr<NiceMock<Gui::ButtonMock>> toExitButton;
    std::unique_ptr<NiceMock<Gui::ButtonListBuilderMock>> dropDownListBuilder;
};

TEST_F(MenuStateButtonActionsTest, mainMenuStateAssignsGameStateWhenToGameButtonIsPressed)
{
    EXPECT_CALL(*(toGameButton), update(_));
    EXPECT_CALL(*(toGameButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(toGameButton))))
        .WillOnce(Return(ByMove(std::move(toSettingsButton))))
        .WillOnce(Return(ByMove(std::move(toEditorButton))))
        .WillOnce(Return(ByMove(std::move(toExitButton))));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            sf::VideoMode(0, 0),
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::GameState));
}

TEST_F(MenuStateButtonActionsTest, mainMenuStateAssignsSettingsStateWhenToSettingsButtonIsPressed)
{
    EXPECT_CALL(*(toSettingsButton), update(_));
    EXPECT_CALL(*(toSettingsButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(toGameButton))))
        .WillOnce(Return(ByMove(std::move(toSettingsButton))))
        .WillOnce(Return(ByMove(std::move(toEditorButton))))
        .WillOnce(Return(ByMove(std::move(toExitButton))));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            sf::VideoMode(0, 0),
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::SettingsState));
}

TEST_F(MenuStateButtonActionsTest, mainMenuStateAssignsEditorStateWhenToEditorButtonIsPressed)
{
    EXPECT_CALL(*(toEditorButton), update(_));
    EXPECT_CALL(*(toEditorButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(toGameButton))))
        .WillOnce(Return(ByMove(std::move(toSettingsButton))))
        .WillOnce(Return(ByMove(std::move(toEditorButton))))
        .WillOnce(Return(ByMove(std::move(toExitButton))));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            sf::VideoMode(0, 0),
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::EditorState));
}

TEST_F(MenuStateButtonActionsTest, mainMenuStateAssignsNullptrWhenToExitButtonIsPressed)
{
    EXPECT_CALL(*(toExitButton), update(_));
    EXPECT_CALL(*(toExitButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(toGameButton))))
        .WillOnce(Return(ByMove(std::move(toSettingsButton))))
        .WillOnce(Return(ByMove(std::move(toEditorButton))))
        .WillOnce(Return(ByMove(std::move(toExitButton))));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            sf::VideoMode(0, 0),
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(sut->getNextState(), nullptr);
}

}