#include <Button.hpp>
#include <ScreenPercentagePoint.hpp>
#include <ButtonTextCalculations.hpp>

namespace Gui
{

MainMenuButton::MainMenuButton(
    const VectorMath::ScreenPercentagePoint& position,
    const VectorMath::ScreenPercentagePoint& size,
    const std::optional<sf::Text> textContent,
    const EventColor& idleColors,
    const EventColor& hoverColors,
    const EventColor& activeColors,
    std::unique_ptr<Events::IButtonEventHandler> eventHandler)
: textContent(textContent),
  background(position, size),
  idleColors(idleColors),
  hoverColors(hoverColors),
  activeColors(activeColors),
  eventHandler(std::move(eventHandler))
{
    initBackground();
    if(textContent)
        initText();
}

void MainMenuButton::initText()
{
    textContent->setCharacterSize(VectorMath::calculateFontSize(background.getSize().toPixels()));
	textContent->setFillColor(idleColors.text);
	textContent->setPosition(VectorMath::calculateTextPosOnBackground(
        background,
        textContent->getGlobalBounds()));
}

void MainMenuButton::initBackground()
{
	background.setFillColor(idleColors.background);
	background.setOutlineColor(idleColors.outline);
}

void MainMenuButton::setColor(const EventColor& colors)
{
    background.setFillColor(colors.background);
    background.setOutlineColor(colors.outline);
    textContent->setFillColor(colors.text);
}

std::optional<sf::Font> MainMenuButton::getFont() const
{
    return textContent ? std::make_optional<sf::Font>(*(textContent->getFont())) : std::nullopt;
}

VectorMath::ScreenPercentagePoint MainMenuButton::getPosition() const
{
    return background.getPosition();
}

VectorMath::ScreenPercentagePoint MainMenuButton::getSize() const
{
    return background.getSize();
}

void MainMenuButton::setTextContent(const sf::Text& text)
{
    textContent = text;
    textContent->setPosition(VectorMath::calculateTextPosOnBackground(
        background,
        textContent->getGlobalBounds()));
}

void MainMenuButton::update(const sf::Vector2i& mousePosOnWindow)
{
    active = false;
    if(background.getGlobalBounds().contains(
        static_cast<sf::Vector2f>(mousePosOnWindow)))
    {
        setColor(hoverColors);
        if(eventHandler->isPressed())
        {
            setColor(activeColors);
            active = true;
        }
    }
    else
        setColor(idleColors);
}

std::unique_ptr<Button> MainMenuButton::clone(const std::optional<sf::Text> targetTextContent, const VectorMath::ScreenPercentagePoint& targetPosition)
{
    auto eventHandler = std::make_unique<Events::ButtonEventHandler>();
    const auto targetText = targetTextContent ? targetTextContent : std::nullopt;
    return std::make_unique<MainMenuButton>(
        targetPosition,
        background.getSize(),
        targetText,
        idleColors,
        hoverColors,
        activeColors,
        std::move(eventHandler));
}

}