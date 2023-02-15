#include <EditorState.hpp>

namespace States
{

EditorState::EditorState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::EditorAssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager))
{
    gui = guiManager->createGui(State::assetsManager->getFont());
}

void EditorState::update(const Core::IWindow& window, const float deltaTime)
{
    gui->update(window.getMousePosition());
}

void EditorState::drawOutput(Core::IWindow& window)
{
    gui->drawTo(window);
}

}