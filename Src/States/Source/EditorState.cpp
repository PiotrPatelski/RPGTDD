#include <EditorState.hpp>
#include <InputListener.hpp>
#include <GuiActions.hpp>
#include <TileMapManager.hpp>

namespace States
{

EditorState::EditorState(
    std::shared_ptr<FileMgmt::IConfigManager> config,
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

    tileMap = tileMapManager->createTileMap();
    currentTileBuilder = tileMapManager->createTileBuilder(*State::assetsManager, *State::configManager);
}

void EditorState::update(const Types::Window& window, const float deltaTime)
{
    const auto currentMousePosition = window.getMousePosition();

    gui->update(currentMousePosition);
    handleAction(gui->getActiveAction());
    handleAction(inputListener->getKeyboardAction());
    if(not paused)
    {
        handleAction(inputListener->getMouseAction(currentMousePosition));
        tileMap->update();
    }
}

void EditorState::handleAction(std::optional<Events::StateAction> action)
{
    if(action.has_value())
        get<Events::GameAction>(action.value())(*this);
}

void EditorState::drawOutput(Types::Window& window)
{
    tileMap->drawTo(window);
    gui->drawTo(window);
}

void EditorState::togglePause()
{
    paused = not paused;
    Events::TogglePause pause;
    gui->acceptRequest(pause);
}

void EditorState::tryTileAdditionAt(const sf::Vector2i& position)
{
    if(tileMap->isValidPosition(position))
        tileMap->addTile(currentTileBuilder->atPosition(position).build());
}

void EditorState::tryTileRemovalAt(const sf::Vector2i& position)
{
    if(tileMap->isValidPosition(position) and not tileMap->isEmptyAt(position))
        tileMap->removeTile(position);
}

}