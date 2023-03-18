#include <ButtonMenu.hpp>
#include <Window.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>

namespace Gui
{

ButtonMenu::ButtonMenu(
    const sf::Text& textContent,
    const Types::Background& background,
    std::vector<ActionButton>&& sections)
: ButtonList(textContent),
  background(background),
  sections(std::move(sections))
{}

void ButtonMenu::update(const sf::Vector2i& currentMousePosition)
{
    for(auto& section : sections)
    {
        section.object->update(currentMousePosition);
    }
}

void ButtonMenu::drawTo(Types::Window& window)
{
    background.drawTo(window);
    window.draw(textContent);
    for(auto& section : sections)
    {
        section.object->getBackground().drawTo(window);
        const auto sectionText = section.object->getTextContent();
        if(sectionText)
            window.draw(*sectionText);
    }
}

std::optional<Events::StateAction> ButtonMenu::getActiveAction()
{
    auto pressedSection = std::find_if(begin(sections), end(sections),
        [](const Gui::ActionButton& button){return button.object->isPressed();});
    if(pressedSection != std::end(sections))
        return std::make_optional<Events::StateAction>(pressedSection->action);
    return std::nullopt;
}

}