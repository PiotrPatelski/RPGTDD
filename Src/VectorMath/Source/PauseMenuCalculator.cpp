#include <PauseMenuCalculator.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>
#include <ButtonTextCalculations.hpp>
#include <Background.hpp>

namespace VectorMath
{

uint PauseMenuCalculator::calculateTextSize(const sf::Vector2f& backgroundSize) const
{
    return calculateFontSize(backgroundSize / 4.f);
}

sf::Vector2f PauseMenuCalculator::calculateTextPosition(const Types::Background& container, const sf::FloatRect& textBounds) const
{
    const float backgroundHalfPositionX = container.getPosition().toPixels().x + container.getSize().toPixels().x / 2.f;
    const float textLengthOffset = textBounds.width / 2.f;
    const float textPositionX = backgroundHalfPositionX - textLengthOffset;
    const float backgroundYOffset = ScreenPercentagePoint(resolution, sf::Vector2f(0.f, 2.f)).toPixels().y;
    const float textPositionY = container.getPosition().toPixels().y + backgroundYOffset;
    return sf::Vector2f(textPositionX, textPositionY);
}

ScreenPercentagePoint PauseMenuCalculator::calculatePositionWithNoButtons(const Types::Background& container) const
{
    const auto offset = sf::Vector2f(container.getSize().toPixels().x / 4 , container.getSize().toPixels().y / 7);
    return PixelsPoint(resolution, (container.getPosition().toPixels() + offset));
}

ScreenPercentagePoint PauseMenuCalculator::calculatePositionRelativeToButtons(
    const ScreenPercentagePoint& firstButtonPosition,
    const ScreenPercentagePoint& lastButtonPosition,
    const ScreenPercentagePoint& lastButtonSize,
    const Types::Background& container) const
{
    const auto lastButtonHeight = lastButtonSize.toPixels().y;
    const auto lastButtonLowerBorderPosition = lastButtonPosition.toPixels() + sf::Vector2f{0, lastButtonHeight};
    const auto buttonSeparationOffset = sf::Vector2f{0, firstButtonPosition.toPixels().y - container.getPosition().toPixels().y};
    return PixelsPoint(resolution, (lastButtonLowerBorderPosition + buttonSeparationOffset));
}

}