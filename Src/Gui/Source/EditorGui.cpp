#include <EditorGui.hpp>
#include <GuiActions.hpp>

namespace Gui
{

void EditorGui::acceptRequest(Events::GuiAction& action)
{
    action.execute(*this);
}

void EditorGui::addButton(std::unique_ptr<IButton> button, Events::StateAction action)
{

}

void EditorGui::addButtonList(std::unique_ptr<ButtonList> list)
{

}

void EditorGui::addPauseMenu(std::unique_ptr<ButtonList> list)
{
    pauseMenu = std::move(list);
}

std::optional<Events::StateAction> EditorGui::getActiveAction()
{

}

void EditorGui::drawTo(Core::IWindow& window)
{
    if(paused)
        pauseMenu->drawTo(window);
}

void EditorGui::update(const sf::Vector2i& currentMousePos)
{
    if(paused)
        pauseMenu->update(currentMousePos);
}

std::optional<Events::StateAction> EditorGui::pollActionFromButtons()
{

}

std::optional<Events::StateAction> EditorGui::pollActionFromButtonLists()
{

}

}