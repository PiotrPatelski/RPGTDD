#include <EditorState.hpp>
#include <InputListener.hpp>
#include <GuiActions.hpp>
#include <TileMapManager.hpp>

namespace States
{

EditorState::EditorState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager,
    std::unique_ptr<Tiles::TileMapManager> tileMapManager,
    std::unique_ptr<Events::InputListener> inputListener)
    : MapState(
        config,
        std::move(assetsManager)),
      inputListener(std::move(inputListener))
{
    gui = guiManager->createGui(State::assetsManager->getFont("MENU_BUTTON"));
    tileMap = tileMapManager->createTileMap(*State::assetsManager);
    currentTileBuilder = tileMapManager->moveTileBuilder();
}

void EditorState::update(const Types::IWindow& window, const float deltaTime)
{
    const auto currentMousePosition = window.getMousePosition();

    gui->update(currentMousePosition);
    handleAction(gui->getActiveAction());
    handleAction(inputListener->getKeyboardAction());
    if(not paused)
    {
        handleAction(inputListener->getMouseAction(currentMousePosition));
    }
}

void EditorState::handleAction(std::optional<Events::StateAction> action)
{
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

void EditorState::addTileAt(const sf::Vector2i& position)
{
    tileMap->addTile(currentTileBuilder->atPosition(position).build());
}

void EditorState::removeTileAt(const sf::Vector2i& position)
{

}

}