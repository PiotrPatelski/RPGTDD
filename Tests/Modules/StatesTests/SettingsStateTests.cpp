#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SettingsState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include <MenuGui.hpp>
#include "AssetsManagerMock.hpp"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"
#include "UserInterfaceMock.hpp"
#include "InputListenerMock.hpp"

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
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        settingsAssetsManager = std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>();
        settingsGuiManager = std::make_unique<NiceMock<Gui::GuiManagerMock>>();
        ON_CALL(*settingsAssetsManager, getTexture(_)).WillByDefault(Return(&texture));
        ON_CALL(*settingsAssetsManager, getFont(_)).WillByDefault(ReturnRef(font));
        dummyConfig.resolution = sf::VideoMode(480, 480);
        ON_CALL(*configManager, getGraphics).WillByDefault(ReturnRef(dummyConfig));
    }
    sf::Texture texture;
    sf::Font font;
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::AssetsManagerMock>> settingsAssetsManager;
    std::unique_ptr<NiceMock<Gui::GuiManagerMock>> settingsGuiManager;
    FileMgmt::GraphicsConfig dummyConfig;
};

TEST_F(SettingsStateTest, stateIsDoneWhenIsReadyToChange)
{
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    sut->finishState();
    ASSERT_TRUE(sut->isReadyToChange());
}

TEST_F(SettingsStateTest, stateIsNotDoneWhenIsNotReadyToChange)
{
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    ASSERT_FALSE(sut->isReadyToChange());
}

TEST_F(SettingsStateTest, settingsStateInitializesBackgroundSizeProperly)
{
    configManager->queueGraphicsRequest(
        [](FileMgmt::GraphicsConfig& gfxConfig)
        {
            gfxConfig.resolution = sf::VideoMode{480,480};
        });

    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    ASSERT_EQ(sut->getBackground()->getSize().x, 480);
    ASSERT_EQ(sut->getBackground()->getSize().y, 480);
}

TEST_F(SettingsStateTest, settingsStateStateInitializesBackgroundTextureProperly)
{
    EXPECT_CALL(*settingsAssetsManager, getTexture(Eq("MENU_BACKGROUND"))).WillOnce(Return(&texture));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    ASSERT_NE(sut->getBackground()->getTexture(), nullptr);
}

TEST_F(SettingsStateTest, settingsStateDrawsOutputProperly)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();

    std::unique_ptr<Gui::UserInterface> gui = std::make_unique<Gui::MenuGui>();
    gui->addButton(std::move(Gui::MenuButtonBuilder().
        withTextContent(sf::Text("testButton1", font)).build()), Events::ToMainMenuState());

    EXPECT_CALL(*settingsGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    EXPECT_CALL(*window, draw(A<const sf::Drawable&>())).Times(3);
    sut->drawOutput(*window);
}

TEST_F(SettingsStateTest, settingsStateUpdatesGuiProperly)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();
    EXPECT_CALL(*window, getMousePosition()).WillOnce(Return(sf::Vector2i{0, 0}));
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, update(A<const sf::Vector2i&>()));
    EXPECT_CALL(*gui, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>([](States::MenuState&){})));

    EXPECT_CALL(*settingsGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    sut->update(*window, 0.f);
}

TEST_F(SettingsStateTest, settingsStateCallsActionReturnedByGui)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();

    MockFunction<void(States::MenuState&)> callback;
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, update(A<const sf::Vector2i&>()));
    EXPECT_CALL(*gui, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));

    EXPECT_CALL(*settingsGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    EXPECT_CALL(callback, Call(A<States::MenuState&>()));
    sut->update(*window, 0.f);
}

TEST_F(SettingsStateTest, settingsStateWontChangeStateIfNulloptIsReturnedByGui)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();

    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, update(A<const sf::Vector2i&>()));
    EXPECT_CALL(*gui, getActiveAction()).WillOnce(Return(
        std::nullopt));

    EXPECT_CALL(*settingsGuiManager, createGui(_)).WillOnce(Return(ByMove(std::move(gui))));
    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::make_unique<NiceMock<Events::InputListenerMock>>());
    sut->update(*window, 0.f);
    ASSERT_EQ(sut->getNextState(), nullptr);
    ASSERT_FALSE(sut->isReadyToChange());
}

TEST_F(SettingsStateTest, settingsStateCallsActionReturnedByInputListener)
{
    auto window = std::make_unique<NiceMock<::Types::WindowMock>>();

    MockFunction<void(States::MenuState&)> callback;
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    ON_CALL(*settingsGuiManager, createGui(_)).WillByDefault(Return(ByMove(
        std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));

    auto inputListener = std::make_unique<NiceMock<Events::InputListenerMock>>();
    EXPECT_CALL(*inputListener, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    FileMgmt::KeyboardConfig keyboardConfig;

    auto sut = std::make_unique<SettingsState>(
        configManager,
        std::move(settingsAssetsManager),
        std::move(settingsGuiManager),
        std::move(inputListener));
    EXPECT_CALL(callback, Call(A<States::MenuState&>()));
    sut->update(*window, 0.f);
}

}