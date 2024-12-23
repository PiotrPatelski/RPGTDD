#include <EditorGui.hpp>
#include <GuiActions.hpp>
#include <Window.hpp>

namespace Gui
{

EditorGui::EditorGui(PauseMenu&& pauseImpl, std::unique_ptr<TileSelector> tileSelectorImpl)
: pauseMenu{std::move(pauseImpl)},
  tileSelector(std::move(tileSelectorImpl))
{}

void EditorGui::acceptRequest(Events::GuiAction& action)
{
    action.execute(*this);
}

void EditorGui::addButton(std::unique_ptr<Button> button, Events::StateAction action)
{

}

void EditorGui::addButtonList(std::unique_ptr<ButtonList> list)
{

}

std::optional<Events::StateAction> EditorGui::getActiveAction()
{
    if(pauseMenu.paused)
    {
        return pauseMenu.impl->getActiveAction();
    }
    return std::nullopt;
}

void EditorGui::drawTo(Types::Window& window)
{
    if(pauseMenu.paused)
    {
        pauseMenu.backgroundShade.drawTo(window);
        pauseMenu.impl->drawTo(window);
    }
}

void EditorGui::togglePause()
{
    pauseMenu.paused = not(pauseMenu.paused);
}

void EditorGui::toggleTileSelector()
{
    tileSelector->toggle();
}

void EditorGui::update(const sf::Vector2i& currentMousePos)
{
    if(pauseMenu.paused)
        pauseMenu.impl->update(currentMousePos);
    else if(tileSelector->isActive())
        tileSelector->update(currentMousePos);
}

std::optional<Events::StateAction> EditorGui::pollActionFromButtons()
{
    return std::nullopt;
}

std::optional<Events::StateAction> EditorGui::pollActionFromButtonLists()
{
    return std::nullopt;
}

}