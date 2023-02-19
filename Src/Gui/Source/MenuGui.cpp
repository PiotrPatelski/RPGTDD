#include <MenuGui.hpp>
#include <Window.hpp>
#include <GuiActions.hpp>


namespace Gui
{

void MenuGui::acceptRequest(Events::GuiAction& action)
{
    action.execute(*this);
}

void MenuGui::addButton(std::unique_ptr<Button> button, Events::StateAction action)
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

void MenuGui::drawTo(Types::IWindow& window)
{
    for(const auto& button : buttons)
    {
        button.object->getBackground().drawTo(window);
        const auto buttonText = button.object->getTextContent();
        if(buttonText)
            window.draw(*buttonText);
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