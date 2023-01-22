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
#include "ButtonBuilderMock.hpp"

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
        texture = std::make_shared<sf::Texture>();
        font = std::make_shared<sf::Font>();;
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        mainMenuAssetsManager = std::make_unique<NiceMock<FileMgmt::MainMenuAssetsManagerMock>>();
        mainMenuGuiManager = std::make_unique<NiceMock<Gui::MainMenuGuiManagerMock>>();
        ON_CALL(*mainMenuAssetsManager, getTexture()).WillByDefault(Return(texture));
        ON_CALL(*mainMenuAssetsManager, getFont()).WillByDefault(Return(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(Return(dummyConfig));
    }
    std::shared_ptr<sf::Texture> texture;
    std::shared_ptr<sf::Font>font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::MainMenuAssetsManagerMock>> mainMenuAssetsManager;
    std::unique_ptr<NiceMock<Gui::MainMenuGuiManagerMock>> mainMenuGuiManager;
    NiceMock<Core::WindowMock> window;
    FileMgmt::GraphicsConfig dummyConfig;
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
    FileMgmt::GraphicsConfig gfxConfig;
    gfxConfig.resolution = sf::VideoMode{480,480};
    configManager->setGraphics(gfxConfig);

    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(MainMenuStateTest, mainMenuStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*mainMenuAssetsManager, getTexture()).WillOnce(Return(std::make_shared<sf::Texture>()));
    auto sut = std::make_unique<MainMenuState>(
        configManager,
        std::move(mainMenuAssetsManager),
        std::move(mainMenuGuiManager));
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(MainMenuStateTest, mainMenuStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<Core::WindowMock>>();

    std::unique_ptr<Gui::IUserInterface> gui = std::make_unique<Gui::UserInterface>();
    auto callback = [](States::MainMenuState&){};
    gui->addButton(Gui::ButtonBuilder(sf::VideoMode(100, 100)).
            withTextContent("testButton1").build(), callback);
    gui->addButton(Gui::ButtonBuilder(sf::VideoMode(100, 100)).
            withTextContent("testButton2").build(), callback);
    gui->addButton(Gui::ButtonBuilder(sf::VideoMode(100, 100)).
            withTextContent("testButton3").build(), callback);
    gui->addButton(Gui::ButtonBuilder(sf::VideoMode(100, 100)).
            withTextContent("testButton4").build(), callback);

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
    auto gameButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(gameButton), update(_));
    EXPECT_CALL(*(gameButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::IUserInterface> gui = std::make_unique<Gui::UserInterface>();
    gui->addButton(std::move(gameButton), Events::ToGameState());

    auto gameAssetsManager = std::make_unique<NiceMock<FileMgmt::GameAssetsManagerMock>>();
    auto gameGuiManager = std::make_unique<NiceMock<Gui::GameGuiManagerMock>>();

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
    auto settingsButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(settingsButton), update(_));
    EXPECT_CALL(*(settingsButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::IUserInterface> gui = std::make_unique<Gui::UserInterface>();
    gui->addButton(std::move(settingsButton), Events::ToSettingsState());

    auto settingsAssetsManager = std::make_unique<NiceMock<FileMgmt::SettingsAssetsManagerMock>>();
    auto settingsGuiManager = std::make_unique<NiceMock<Gui::SettingsGuiManagerMock>>();

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
    auto editorButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(editorButton), update(_));
    EXPECT_CALL(*(editorButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::IUserInterface> gui = std::make_unique<Gui::UserInterface>();
    gui->addButton(std::move(editorButton), Events::ToEditorState());

    auto editorAssetsManager = std::make_unique<NiceMock<FileMgmt::EditorAssetsManagerMock>>();
    auto editorGuiManager = std::make_unique<NiceMock<Gui::EditorGuiManagerMock>>();

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
    auto exitButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
    EXPECT_CALL(*(exitButton), update(_));
    EXPECT_CALL(*(exitButton), isPressed()).WillOnce(Return(true));

    std::unique_ptr<Gui::IUserInterface> gui = std::make_unique<Gui::UserInterface>();
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

struct MainMenuStateButtonActionsTest : public MainMenuStateTest
{
    MainMenuStateButtonActionsTest()
    {
        buttonBuilder = std::make_unique<NiceMock<Gui::ButtonBuilderMock>>();
        ON_CALL(*buttonBuilder, withTextContent(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withFont(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, atPosition(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withSize(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
        toGameButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
        toSettingsButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
        toEditorButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
        toExitButton = std::make_shared<NiceMock<Gui::ButtonMock>>();
    }
    std::unique_ptr<NiceMock<Gui::ButtonBuilderMock>> buttonBuilder;
    std::shared_ptr<NiceMock<Gui::ButtonMock>> toGameButton;
    std::shared_ptr<NiceMock<Gui::ButtonMock>> toSettingsButton;
    std::shared_ptr<NiceMock<Gui::ButtonMock>> toEditorButton;
    std::shared_ptr<NiceMock<Gui::ButtonMock>> toExitButton;
};

TEST_F(MainMenuStateButtonActionsTest, mainMenuStateAssignsGameStateWhenToGameButtonIsPressed)
{
    EXPECT_CALL(*(toGameButton), update(_));
    EXPECT_CALL(*(toGameButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(toGameButton))
        .WillOnce(Return(toSettingsButton))
        .WillOnce(Return(toEditorButton))
        .WillOnce(Return(toExitButton));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::GameState));
}

TEST_F(MainMenuStateButtonActionsTest, mainMenuStateAssignsSettingsStateWhenToSettingsButtonIsPressed)
{
    EXPECT_CALL(*(toSettingsButton), update(_));
    EXPECT_CALL(*(toSettingsButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(toGameButton))
        .WillOnce(Return(toSettingsButton))
        .WillOnce(Return(toEditorButton))
        .WillOnce(Return(toExitButton));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::SettingsState));
}

TEST_F(MainMenuStateButtonActionsTest, mainMenuStateAssignsEditorStateWhenToEditorButtonIsPressed)
{
    EXPECT_CALL(*(toEditorButton), update(_));
    EXPECT_CALL(*(toEditorButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(toGameButton))
        .WillOnce(Return(toSettingsButton))
        .WillOnce(Return(toEditorButton))
        .WillOnce(Return(toExitButton));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(typeid(*(sut->getNextState())), typeid(States::EditorState));
}

TEST_F(MainMenuStateButtonActionsTest, mainMenuStateAssignsNullptrWhenToExitButtonIsPressed)
{
    EXPECT_CALL(*(toExitButton), update(_));
    EXPECT_CALL(*(toExitButton), isPressed()).WillOnce(Return(true));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(toGameButton))
        .WillOnce(Return(toSettingsButton))
        .WillOnce(Return(toEditorButton))
        .WillOnce(Return(toExitButton));
    auto sut = std::make_unique<MainMenuState>(
        std::make_shared<Core::ConfigManager>(),
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::move(buttonBuilder)
        ));
    sut->update(window, 0.f);
    ASSERT_EQ(sut->getNextState(), nullptr);
}

}