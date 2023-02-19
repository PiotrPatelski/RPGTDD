#include <ScreenPercentagePoint.hpp>
#include <PixelsPoint.hpp>

namespace VectorMath
{

ScreenPercentagePoint::ScreenPercentagePoint(const sf::VideoMode& resolution, const sf::Vector2f& screenPercentage)
: resolution(resolution),
  val(screenPercentage)
{}

ScreenPercentagePoint::ScreenPercentagePoint(const ScreenPercentagePoint& screenPercentage)
: resolution(screenPercentage.resolution),
    val(screenPercentage.val)
{}

ScreenPercentagePoint::ScreenPercentagePoint(ScreenPercentagePoint&& screenPercentage)
: resolution(screenPercentage.resolution),
    val(screenPercentage.val)
{}

ScreenPercentagePoint::ScreenPercentagePoint(const PixelsPoint& pixelsPoint)
: resolution(pixelsPoint.getResolution()),
    val(pixelsPoint.toScreenPercentage())
{}

ScreenPercentagePoint& ScreenPercentagePoint::operator=(const ScreenPercentagePoint& other)
{
    if(this->val != other.value())
    {
        resolution = other.getResolution();
        val = other.value();
    }
    return *this;
}

ScreenPercentagePoint& ScreenPercentagePoint::operator=(ScreenPercentagePoint&& other)
{
    std::swap(resolution, other.resolution);
    std::swap(val, other.val);
    return *this;
}

sf::VideoMode ScreenPercentagePoint::getResolution() const
{
    return resolution;
}

sf::Vector2f ScreenPercentagePoint::toPixels() const
{
    return sf::Vector2f(toPixelsOnX(val.x), toPixelsOnY(val.y));
}

sf::Vector2f ScreenPercentagePoint::value() const
{
    return val;
}

float ScreenPercentagePoint::toPixelsOnX(const float percentage) const
{
    return static_cast<float>(resolution.width) * percentage / 100.f;
}

float ScreenPercentagePoint::toPixelsOnY(const float percentage) const
{
    return static_cast<float>(resolution.height) * percentage / 100.f;
}

}