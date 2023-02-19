#include <EditorGui.hpp>
#include <GuiActions.hpp>
#include <Window.hpp>

namespace Gui
{

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

void EditorGui::addPauseMenu(PauseMenu&& list)
{
    pauseMenu = std::move(list);
}

std::optional<Events::StateAction> EditorGui::getActiveAction()
{
    return std::nullopt;
}

void EditorGui::drawTo(Types::IWindow& window)
{
    if(pauseMenu.paused)
    {
        window.draw(pauseMenu.backgroundShade);
        pauseMenu.impl->drawTo(window);
    }
}

void EditorGui::update(const sf::Vector2i& currentMousePos)
{
    if(pauseMenu.paused)
        pauseMenu.impl->update(currentMousePos);
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