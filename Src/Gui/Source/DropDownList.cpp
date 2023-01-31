#include <DropDownList.hpp>
#include <Window.hpp>

namespace Gui
{

MenuDropDownList::MenuDropDownList(
    const sf::Text& textContent,
    std::unique_ptr<IButton> initiatingButton)
: initiatingButton(ActionButton{std::move(initiatingButton), std::monostate{}}),
  textContent(textContent),
  active(false)
{

}

void MenuDropDownList::addSection(const std::string& name, Events::StateAction action)
{
    sf::Vector2f sectionPosition = calculateNextSectionPosition();
    sections.push_back(
        ActionButton{
            initiatingButton.object->clone(name, sectionPosition),
            action});
}

sf::Vector2f MenuDropDownList::calculateNextSectionPosition()
{
   if(sections.empty())
        return initiatingButton.object->getPosition() + sf::Vector2f{0, initiatingButton.object->getSize().y};
    else
        return sections.back().object->getPosition() + sf::Vector2f{0, sections.back().object->getSize().y};
}

void MenuDropDownList::update(const sf::Vector2i& currentMousePosition)
{
    initiatingButton.object->update(currentMousePosition);
    if(initiatingButton.object->isPressed())
        active = not active;
    if(active)
        initiatingButton.action = findActiveAction(currentMousePosition);
}

void MenuDropDownList::drawTo(Core::IWindow& window)
{
    window.draw(initiatingButton.object->getBackground());
    window.draw(initiatingButton.object->getTextContent());
    if(active)
    {
        drawSections(window);
    }
}

void MenuDropDownList::drawSections(Core::IWindow& window)
{
    for(const auto& section : sections)
    {
        window.draw(section.object->getBackground());
        window.draw(section.object->getTextContent());
    }
}

Events::StateAction MenuDropDownList::findActiveAction(const sf::Vector2i& currentMousePosition)
{
    for (auto& section : sections)
    {
        section.object->update(currentMousePosition);
    }
    auto pressedSection = std::find_if(begin(sections), end(sections),
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    return (pressedSection != std::end(sections)) ? pressedSection->action : std::monostate{};
}

std::optional<Events::StateAction> MenuDropDownList::getActiveAction()
{
    if(std::holds_alternative<std::monostate>(initiatingButton.action))
        return std::nullopt;
    return std::make_optional<Events::StateAction>(initiatingButton.action);
}

}