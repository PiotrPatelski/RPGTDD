#pragma once

#include <SFML/Window.hpp>

namespace VectorMath
{

class PixelsPoint;

class ScreenPercentagePoint
{
public:
    ScreenPercentagePoint(const sf::VideoMode&, const sf::Vector2f&);
    ScreenPercentagePoint(const ScreenPercentagePoint&);
    ScreenPercentagePoint(ScreenPercentagePoint&&);
    ScreenPercentagePoint(const PixelsPoint&);
    ~ScreenPercentagePoint(){}
    ScreenPercentagePoint& operator=(const ScreenPercentagePoint&);
    ScreenPercentagePoint& operator=(ScreenPercentagePoint&&);
    sf::VideoMode getResolution() const;
    sf::Vector2f toPixels() const;
    sf::Vector2f value() const;
private:
    float toPixelsOnX(const float) const;
    float toPixelsOnY(const float) const;
    sf::VideoMode resolution;
    sf::Vector2f val;
};

}