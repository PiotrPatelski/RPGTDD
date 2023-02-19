#include <EditorState.hpp>
#include <InputListener.hpp>
#include <GuiActions.hpp>

namespace States
{

EditorState::EditorState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager,
    std::unique_ptr<Events::InputListener> inputListener)
    : MapState(
        config,
        std::move(assetsManager)),
      inputListener(std::move(inputListener))
{
    gui = guiManager->createGui(State::assetsManager->getFont("MENU_BUTTON"));
}

void EditorState::update(const Types::IWindow& window, const float deltaTime)
{
    gui->update(window.getMousePosition());
    auto action = inputListener->getActiveAction();
    if(action.has_value())
        get<Events::GameAction>(action.value())(*this);
}

void EditorState::drawOutput(Types::IWindow& window)
{
    gui->drawTo(window);
}

void EditorState::togglePause()
{
    paused = not paused;
    Events::TogglePause pause;
    gui->acceptRequest(pause);
}

}