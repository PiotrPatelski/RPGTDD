#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorGuiManager.hpp>
#include <ButtonBuilderMock.hpp>
#include <GuiActions.hpp>

namespace Gui
{

using namespace ::testing;

struct EditorGuiManagerTest : public ::testing::Test
{

};

TEST_F(EditorGuiManagerTest, emptyEditorGuiManagerCreated)
{
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    auto sut = std::make_unique<EditorGuiManager>(std::move(buttonBuilder));
    auto gui = sut->createGui(std::make_shared<sf::Font>());
    Events::TogglePause action;
    gui->acceptRequest(action);
}

}