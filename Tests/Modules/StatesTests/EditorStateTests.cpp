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

// #define TEST_PATH _PROJECT_ROOT_FOLDER"/TestResources"

namespace States
{

using namespace ::testing;

struct EditorStateTest : public testing::Test
{
    EditorStateTest()
    {
        configManager = std::make_shared<NiceMock<Core::ConfigManagerMock>>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::EditorAssetsManagerMock>>();
        guiManager = std::make_unique<NiceMock<Gui::GuiManagerMock>>();
    }
    std::shared_ptr<Core::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::EditorAssetsManagerMock>> assetsManager;
    std::unique_ptr<NiceMock<Gui::GuiManagerMock>> guiManager;
};

TEST_F(EditorStateTest, editorStateInitializesGuiWithManager)
{
    EXPECT_CALL(*guiManager, createGui(A<std::shared_ptr<sf::Font>>())).WillOnce
        (Return(ByMove(std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
}

TEST_F(EditorStateTest, editorStateUpdatesCreatedGuiWithMousePosition)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    NiceMock<Core::WindowMock> window;
    const float deltaTimme = 0.f;
    const sf::Vector2i mousePosition{30, 30};
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(mousePosition));
    EXPECT_CALL(*gui, update(Eq(mousePosition)));
    EXPECT_CALL(*guiManager, createGui(A<std::shared_ptr<sf::Font>>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut.update(window, deltaTimme);
}

TEST_F(EditorStateTest, editorStateDrawsCreatedGuiWithWindow)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    NiceMock<Core::WindowMock> window;
    EXPECT_CALL(*gui, drawTo(A<Core::IWindow&>()));
    EXPECT_CALL(*guiManager, createGui(A<std::shared_ptr<sf::Font>>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EditorState sut(
        configManager,
        std::move(assetsManager),
        std::move(guiManager));
    sut.drawOutput(window);
}

}