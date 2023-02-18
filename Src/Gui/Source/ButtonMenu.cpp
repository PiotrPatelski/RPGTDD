#include <ButtonMenu.hpp>
#include <Window.hpp>

namespace Gui
{

ButtonMenu::ButtonMenu(
    const std::string& menuTitle,
    const sf::Font& font,
    const sf::VideoMode& resolution,
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    std::unique_ptr<ButtonBuilder> buttonBuilder)
: ButtonList(sf::Text(menuTitle, font)),
  buttonBuilder(std::move(buttonBuilder))
{
    //TODO CREATE BUILDER FOR THIS CLASS THAT HANDLES THIS INITIALIZATION
    background.setSize(sf::Vector2f(static_cast<float>(resolution.width),
									static_cast<float>(resolution.height)));
	background.setFillColor(sf::Color(20, 20, 20, 100));

    container.setSize(size);
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(position);

    ButtonList::textContent.setPosition(calculateTextPosition(resolution));
    ButtonList::textContent.setFillColor(sf::Color(255, 255, 255, 200));
    ButtonList::textContent.setCharacterSize(calculateFontSize(size));
}

sf::Vector2f ButtonMenu::calculateTextPosition(const sf::VideoMode& resolution)
{
    const float containerHalfPositionX = container.getPosition().x + container.getSize().x / 2.f;
    const float textLengthOffset = textContent.getGlobalBounds().width / 2.f;
    const float textPositionX = containerHalfPositionX - textLengthOffset;
    const float containerYOffset = ScreenPercentage(resolution).toPixelsOnY(4.f);
    const float textPositionY = container.getPosition().y + containerYOffset;
    return sf::Vector2f(textPositionX, textPositionY);
}

sf::Vector2f ButtonMenu::calculateNextSectionPosition()
{
    if(sections.empty())
        return calculatePositionWithNoButtons();
    else
    {
        return calculatePositionRelativeToLastButton();
    }
}

sf::Vector2f ButtonMenu::calculatePositionWithNoButtons()
{
    const auto offset = sf::Vector2f(0.f , container.getSize().y / 3);
    return container.getPosition() + offset;
}

sf::Vector2f ButtonMenu::calculatePositionRelativeToLastButton()
{
    const auto lastButtonPosition = sections.back().object->getPosition();
    const auto lastButtonHeight = sections.back().object->getSize().y;
    const auto lastButtonLowerBorderPosition = lastButtonPosition + sf::Vector2f{0, lastButtonHeight};
    const auto buttonSeparationOffset = sf::Vector2f{0, container.getPosition().y - sections.front().object->getPosition().y};
    return lastButtonLowerBorderPosition + buttonSeparationOffset;
}

void ButtonMenu::addSection(const std::optional<sf::Text> name, Events::StateAction action)
{
    const auto nextSectionPosition = calculateNextSectionPosition();
    const auto sectionSize = sf::Vector2f(container.getSize().x / 2, container.getSize().y / 6);

    if(name)
        *buttonBuilder = buttonBuilder->withTextContent(*name);
    auto button = buttonBuilder
        ->atPosition(nextSectionPosition.x, nextSectionPosition.y)
        .withSize(sectionSize.x, sectionSize.y)
        .build();
    sections.push_back(ActionButton{std::move(button), action});
}

void ButtonMenu::update(const sf::Vector2i& currentMousePosition)
{
    for(auto& section : sections)
    {
        section.object->update(currentMousePosition);
    }
}

void ButtonMenu::drawTo(Core::IWindow& window)
{
    window.draw(background);
    window.draw(container);
    window.draw(textContent);
    for(auto& section : sections)
    {
        window.draw(section.object->getBackground());
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
//TODO MAKE EDITOR GUI WITH THIS AS PAUSE MENU