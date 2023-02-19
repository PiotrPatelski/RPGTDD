#include <PixelsPoint.hpp>
#include <ScreenPercentagePoint.hpp>

namespace VectorMath
{

PixelsPoint::PixelsPoint(const sf::VideoMode& resolution, const sf::Vector2f& pixelsPoint)
: resolution(resolution),
    val(pixelsPoint)
{}

PixelsPoint::PixelsPoint(const ScreenPercentagePoint& screenPercentage)
: resolution(screenPercentage.getResolution()),
    val(screenPercentage.toPixels())
{}

PixelsPoint::PixelsPoint(const PixelsPoint& pixelsPoint)
: resolution(pixelsPoint.resolution),
    val(pixelsPoint.val)
{}

PixelsPoint::PixelsPoint(PixelsPoint&& pixelsPoint)
: resolution(pixelsPoint.resolution),
    val(pixelsPoint.val)
{}

PixelsPoint& PixelsPoint::operator=(const PixelsPoint& other)
{
    if(this->val != other.value())
    {
        resolution = other.getResolution();
        val = other.value();
    }
    return *this;
}

PixelsPoint& PixelsPoint::operator=(PixelsPoint&& other)
{
    std::swap(resolution, other.resolution);
    std::swap(val, other.val);
    return *this;
}

sf::VideoMode PixelsPoint::getResolution() const
{
    return resolution;
}

sf::Vector2f PixelsPoint::toScreenPercentage() const
{
    return sf::Vector2f(toScreenPercentageOnX(val.x), toScreenPercentageOnY(val.y));
}

sf::Vector2f PixelsPoint::value() const
{
    return val;
}

float PixelsPoint::toScreenPercentageOnX(const float pixels) const
{
    return 100.f * pixels / static_cast<float>(resolution.width);
}

float PixelsPoint::toScreenPercentageOnY(const float pixels) const
{
    return 100.f * pixels / static_cast<float>(resolution.height);
}

}