#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include <EditorGui.hpp>
#include "AssetsManagerMock.hpp"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"
#include "UserInterfaceMock.hpp"
#include "InputListenerMock.hpp"

namespace States
{

using namespace ::testing;

struct EditorStateTest : public testing::Test
{
    EditorStateTest()
    {
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>();
        guiManager = std::make_unique<NiceMock<Gui::GuiManagerMock>>();
        inputListener = std::make_unique<NiceMock<Events::InputListenerMock>>();
        ON_CALL(*assetsManager, getFont(_)).WillByDefault(ReturnRef(font));
        ON_CALL(*guiManager, createGui(_)).WillByDefault(Return(ByMove(std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));
    }
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::AssetsManagerMock>> assetsManager;
    std::unique_ptr<NiceMock<Gui::GuiManagerMock>> guiManager;
    std::unique_ptr<NiceMock<Events::InputListenerMock>> inputListener;
    NiceMock<::Types::WindowMock> window;
    sf::Font font;
};

TEST_F(EditorStateTest, editorStateInitializesGuiWithManager)
{
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));
}

TEST_F(EditorStateTest, editorStateUpdatesCreatedGuiWithMousePosition)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();

    const float deltaTimme = 0.f;
    const sf::Vector2i mousePosition{30, 30};
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(mousePosition));
    EXPECT_CALL(*gui, update(Eq(mousePosition)));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));
    sut.update(window, deltaTimme);
}

TEST_F(EditorStateTest, editorStateDrawsCreatedGuiWithWindow)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();

    EXPECT_CALL(*gui, drawTo(A<::Types::IWindow&>()));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));
    sut.drawOutput(window);
}

TEST_F(EditorStateTest, editorStateCallsGuiWhenPaused)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, acceptRequest(A<Events::GuiAction&>()));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));
    sut.togglePause();
}

TEST_F(EditorStateTest, editorStateCallsActionReturnedByInputListener)
{
    MockFunction<void(States::MapState&)> callback;
    EXPECT_CALL(*inputListener, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    EXPECT_CALL(callback, Call(A<States::MapState&>()));
    FileMgmt::KeyboardConfig keyboardConfig;
    
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));

    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateCallsActionReturnedByGui)
{
    MockFunction<void(States::MapState&)> callback;
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EXPECT_CALL(callback, Call(A<States::MapState&>()));
    FileMgmt::KeyboardConfig keyboardConfig;

    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputListener));

    sut.update(window, 0.f);
}

}