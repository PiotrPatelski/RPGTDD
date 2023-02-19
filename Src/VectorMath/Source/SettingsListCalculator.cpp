#include <SettingsListCalculator.hpp>
#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>

namespace VectorMath
{

VectorMath::ScreenPercentagePoint SettingsListCalculator::calculatePositionBelow(
    const VectorMath::ScreenPercentagePoint& position,
    const VectorMath::ScreenPercentagePoint& size) const
{
        const auto buttonHeight = sf::Vector2f{0, size.toPixels().y};
        const auto newSectionPosition = VectorMath::PixelsPoint(
            position.getResolution(),
            (position.toPixels() + buttonHeight));
        return newSectionPosition;
}

sf::Vector2f SettingsListCalculator::textPositionOverButton(const VectorMath::ScreenPercentagePoint& position) const
{
    const auto offset = VectorMath::ScreenPercentagePoint(position.getResolution(), {0.5f, -3.f});
    return position.toPixels() + offset.toPixels();
}



}