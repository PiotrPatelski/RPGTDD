#include <GameGui.hpp>
#include <GuiActions.hpp>

namespace Gui
{

void GameGui::acceptRequest(Events::GuiAction& action)
{
    action.execute(*this);
}

void GameGui::addButton(std::unique_ptr<Button> button, Events::StateAction action)
{

}

void GameGui::addButtonList(std::unique_ptr<ButtonList> list)
{

}

std::optional<Events::StateAction> GameGui::getActiveAction()
{
    return std::nullopt;
}

void GameGui::drawTo(Core::IWindow& window)
{

}

void GameGui::update(const sf::Vector2i& currentMousePos)
{

}

std::optional<Events::StateAction> GameGui::pollActionFromButtons()
{
    return std::nullopt;
}

std::optional<Events::StateAction> GameGui::pollActionFromButtonLists()
{
    return std::nullopt;
}

}