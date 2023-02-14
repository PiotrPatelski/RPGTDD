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

std::optional<Events::StateAction> EditorGui::getActiveAction()
{

}

void EditorGui::drawTo(Core::IWindow& window)
{

}

void EditorGui::update(const sf::Vector2i& currentMousePos)
{

}

std::optional<Events::StateAction> EditorGui::pollActionFromButtons()
{

}

std::optional<Events::StateAction> EditorGui::pollActionFromButtonLists()
{

}

}