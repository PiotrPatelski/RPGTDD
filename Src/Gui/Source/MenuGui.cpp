#include <MenuGui.hpp>
#include <Window.hpp>


namespace Gui
{

void MenuGui::addButton(std::unique_ptr<IButton> button, Events::StateAction action)
{
    buttons.push_back(ActionButton{std::move(button), action});
}

void MenuGui::addButtonList(std::unique_ptr<ButtonList> list)
{
    dropDownLists.push_back(std::move(list));
}

std::optional<Events::StateAction> MenuGui::getActiveAction()
{
    auto action = pollActionFromButtons();
    if(action == std::nullopt)
        action = pollActionFromButtonLists();
    return action;
}

void MenuGui::drawTo(Core::IWindow& window)
{
    for(const auto& button : buttons)
    {
        window.draw(button.object->getBackground());
        window.draw(button.object->getTextContent());
    }
    for(auto& list : dropDownLists)
    {
        list->drawTo(window);
    }
}

void MenuGui::update(const sf::Vector2i& currentMousePos)
{
    for (auto& button : buttons)
    {
        button.object->update(currentMousePos);
    }
    for (auto& list : dropDownLists)
    {
        list->update(currentMousePos);
    }
}

std::optional<Events::StateAction> MenuGui::pollActionFromButtons()
{
    auto activeButton = std::find_if(begin(buttons), end(buttons),
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    if(activeButton != std::end(buttons))
        return std::make_optional<Events::StateAction>(activeButton->action);
    return std::nullopt;
}

std::optional<Events::StateAction> MenuGui::pollActionFromButtonLists()
{
    for (auto& list : dropDownLists)
    {
        auto action = list->getActiveAction();
        if(action != std::nullopt)
            return action;
    }
    return std::nullopt;
}

}