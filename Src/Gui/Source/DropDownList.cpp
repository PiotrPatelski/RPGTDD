#include <DropDownList.hpp>
#include <Window.hpp>
#include <PixelsPoint.hpp>
#include <ScreenPercentagePoint.hpp>

namespace Gui
{

DropDownList::DropDownList(
    const sf::Text& textContent,
    std::unique_ptr<Button> initiatingButton,
    std::vector<ActionButton>&& sections)
: ButtonList(textContent),
  initiatingButton(ActionButton{std::move(initiatingButton), std::monostate{}}),
  sections(std::move(sections))
{}

void DropDownList::update(const sf::Vector2i& currentMousePosition)
{
    initiatingButton.object->update(currentMousePosition);
    if(initiatingButton.object->isPressed())
        active = not active;
    if(active)
    {
        updateSections(currentMousePosition);
        onAction();
    }
}

void DropDownList::updateSections(const sf::Vector2i& currentMousePosition)
{
    for (auto& section : sections)
    {
        section.object->update(currentMousePosition);
    }
}

void DropDownList::onAction()
{
    auto pressedSection = std::find_if(begin(sections), end(sections),
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    applyActiveSectionAction(pressedSection);
    applyActiveSectionText(pressedSection);
}

void DropDownList::applyActiveSectionAction(std::vector<ActionButton>::iterator pressedSection)
{
    if (pressedSection != std::end(sections))
    {
        initiatingButton.action = pressedSection->action;
    }
    else
        initiatingButton.action = std::monostate{};
}

void DropDownList::applyActiveSectionText(std::vector<ActionButton>::iterator pressedSection)
{
    if (pressedSection != std::end(sections))
    {
        auto sectionText = pressedSection->object->getTextContent();
        if(sectionText)
        {
            sectionText->setPosition(initiatingButton.object->getTextContent()->getPosition());
            initiatingButton.object->setTextContent(*sectionText);
        }
    }
}

std::optional<Events::StateAction> DropDownList::getActiveAction()
{
    if(std::holds_alternative<std::monostate>(initiatingButton.action))
        return std::nullopt;
    return std::make_optional<Events::StateAction>(initiatingButton.action);
}

void DropDownList::drawTo(Types::IWindow& window)
{
    window.draw(textContent);
    drawInitButton(window);
    if(active)
        drawSections(window);
}

void DropDownList::drawInitButton(Types::IWindow& window)
{
    initiatingButton.object->getBackground().drawTo(window);
    const auto& buttonText = initiatingButton.object->getTextContent();
    if(buttonText)
        window.draw(*buttonText);
}
void DropDownList::drawSections(Types::IWindow& window)
{
    for(const auto& section : sections)
    {
        section.object->getBackground().drawTo(window);
        const auto& sectionText = section.object->getTextContent();
        if(sectionText)
            window.draw(*sectionText);
    }
}

}