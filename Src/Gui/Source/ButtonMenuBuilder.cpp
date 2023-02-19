#include <ButtonMenuBuilder.hpp>
#include <ButtonMenu.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <ButtonBuilder.hpp>
#include <PauseMenuCalculator.hpp>

namespace Gui
{
ButtonMenuBuilder::ButtonMenuBuilder(){}

ButtonMenuBuilder& ButtonMenuBuilder::withTextContent(const sf::Text& name)
{
    textContent = name;
    textContent.setFillColor(sf::Color(255, 255, 255, 200));
    return *this;
}

ButtonMenuBuilder& ButtonMenuBuilder::withSection(const std::optional<sf::Text> name, Events::StateAction action)
{
    const auto sectionSize = sf::Vector2f(background.getSize().value().x / 2, background.getSize().value().y / 12); //CALCULATE
    if(name)
        buttonBuilder = buttonBuilder.withTextContent(*name);
    auto button = buttonBuilder
        .atPosition(calculateNextSectionPosition())
        .withSize(VectorMath::ScreenPercentagePoint(resolution, sectionSize))
        .build();

    sections.push_back(ActionButton{std::move(button), action});
    return *this;
}

ButtonMenuBuilder& ButtonMenuBuilder::atPosition(const VectorMath::ScreenPercentagePoint& position)
{
    background.setPosition(position);
    resolution = position.getResolution();
    return *this;
}

ButtonMenuBuilder& ButtonMenuBuilder::withSize(const VectorMath::ScreenPercentagePoint& size)
{
    background.setSize(size);
    resolution = size.getResolution();
    return *this;
}

std::unique_ptr<ButtonList> ButtonMenuBuilder::build()
{
    const VectorMath::PauseMenuCalculator calculator(resolution);
    textContent.setCharacterSize(calculator.calculateTextSize(background.getSize().toPixels()));
    textContent.setPosition(calculator.calculateTextPosition(background, textContent.getGlobalBounds()));
    background.setFillColor(sf::Color(20, 20, 20, 200));

    return std::make_unique<ButtonMenu>(
        textContent,
        background,
        std::move(sections));
}

VectorMath::ScreenPercentagePoint ButtonMenuBuilder::calculateNextSectionPosition()
{
    const VectorMath::PauseMenuCalculator calculator(resolution);
    if(sections.empty())
        return calculator.calculatePositionWithNoButtons(background);
    else
    {
        return calculator.calculatePositionRelativeToButtons(
            sections.front().object->getPosition(),
            sections.back().object->getPosition(),
            sections.back().object->getSize(),
            background);
    }
}

}