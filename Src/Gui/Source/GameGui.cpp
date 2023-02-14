#include <GameGui.hpp>
#include <GuiActions.hpp>

namespace Gui
{

void GameGui::acceptRequest(Events::GuiAction& action)
{
    action.execute(*this);
}

void GameGui::addButton(std::unique_ptr<IButton> button, Events::StateAction action)
{

}

void GameGui::addButtonList(std::unique_ptr<ButtonList> list)
{

}

std::optional<Events::StateAction> GameGui::getActiveAction()
{

}

void GameGui::drawTo(Core::IWindow& window)
{

}

void GameGui::update(const sf::Vector2i& currentMousePos)
{

}

std::optional<Events::StateAction> GameGui::pollActionFromButtons()
{

}

std::optional<Events::StateAction> GameGui::pollActionFromButtonLists()
{

}

}