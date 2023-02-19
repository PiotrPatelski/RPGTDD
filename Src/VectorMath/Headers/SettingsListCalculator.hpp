#pragma once
#include <SFML/Window.hpp>

namespace VectorMath
{

class ScreenPercentagePoint;

class SettingsListCalculator
{
public:
    SettingsListCalculator() = default;
    virtual ~SettingsListCalculator() = default;
    sf::Vector2f textPositionOverButton(const VectorMath::ScreenPercentagePoint&) const;
    VectorMath::ScreenPercentagePoint calculatePositionBelow(
        const VectorMath::ScreenPercentagePoint&,
        const VectorMath::ScreenPercentagePoint&) const;
};

}