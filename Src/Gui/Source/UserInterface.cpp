#include <UserInterface.hpp>
#include <Window.hpp>


namespace Gui
{

void UserInterface::addButton(std::shared_ptr<IButton> button, Events::StateAction action)
{
    buttons.push_back(ActionButton{std::move(button), action});
}

std::optional<Events::StateAction> UserInterface::getActiveAction()
{
    auto activeButton = std::find_if(begin(buttons), end(buttons), 
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    if(activeButton != std::end(buttons))
        return std::make_optional<Events::StateAction>(activeButton->action);
    return std::nullopt;
}

void UserInterface::drawTo(Core::IWindow& window)
{
    for(const auto& button : buttons)
    {
        window.draw(button.object->getBackground());
        window.draw(button.object->getTextContent());
    }
}

void UserInterface::update(const Core::IWindow& window)//TODO: we might need input from gameObj like player hp items etc. BUT i dont think we will need whole window. Mouse position should be enough
{
    for (auto& button : buttons)
    {
        button.object->update(window.getMousePosition());
    }
}

}