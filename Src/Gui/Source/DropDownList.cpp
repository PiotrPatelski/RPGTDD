#include <DropDownList.hpp>
#include <Window.hpp>

namespace Gui
{

DropDownList::DropDownList(
    const sf::Text& textContent,
    std::unique_ptr<Button> initiatingButton)
: ButtonList(textContent),
  initiatingButton(ActionButton{std::move(initiatingButton), std::monostate{}})
{
    setTextPosition();
}

void DropDownList::setTextPosition()
{
    const auto listPosition = this->initiatingButton.object->getPosition();
    const float xOffset = 13.0f;
    const float yOffset = -40.f;
    auto textPosition = listPosition + sf::Vector2f{xOffset, yOffset};
    if(textPosition.y < 0)
        textPosition.y = 0;
    ButtonList::textContent.setPosition(textPosition);
}

void DropDownList::addSection(const std::optional<sf::Text> name, Events::StateAction action)
{
    sf::Vector2f sectionPosition = calculateNextSectionPosition();
    sections.push_back(
        ActionButton{
            initiatingButton.object->clone(name, sectionPosition),
            action});
}

sf::Vector2f DropDownList::calculateNextSectionPosition()
{
   if(sections.empty())
        return initiatingButton.object->getPosition() + sf::Vector2f{0, initiatingButton.object->getSize().y};
    else
        return sections.back().object->getPosition() + sf::Vector2f{0, sections.back().object->getSize().y};
}

void DropDownList::update(const sf::Vector2i& currentMousePosition)
{
    initiatingButton.object->update(currentMousePosition);
    if(initiatingButton.object->isPressed())
        active = not active;
    if(active)
        initiatingButton.action = findActiveAction(currentMousePosition);
}

void DropDownList::drawTo(Core::IWindow& window)
{
    window.draw(textContent);
    window.draw(initiatingButton.object->getBackground());
    const auto& buttonText = initiatingButton.object->getTextContent();
    if(buttonText)
        window.draw(*buttonText);
    if(active)
    {
        drawSections(window);
    }
}

void DropDownList::drawSections(Core::IWindow& window)
{
    for(const auto& section : sections)
    {
        window.draw(section.object->getBackground());
        const auto& sectionText = section.object->getTextContent();
        if(sectionText)
            window.draw(*sectionText);
    }
}

Events::StateAction DropDownList::findActiveAction(const sf::Vector2i& currentMousePosition)
{
    for (auto& section : sections)
    {
        section.object->update(currentMousePosition);
    }
    auto pressedSection = std::find_if(begin(sections), end(sections),
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    return (pressedSection != std::end(sections)) ? pressedSection->action : std::monostate{};
}

std::optional<Events::StateAction> DropDownList::getActiveAction()
{
    if(std::holds_alternative<std::monostate>(initiatingButton.action))
        return std::nullopt;
    return std::make_optional<Events::StateAction>(initiatingButton.action);
}

}