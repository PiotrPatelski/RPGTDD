#pragma once

#include <Button.hpp>
#include <StateActions.hpp>

namespace Gui
{

uint calculateFontSize(const sf::Vector2f&);

class ScreenPercentage
{
public:
    ScreenPercentage(const sf::VideoMode& resolution)
    : screenWidth(resolution.width),
      screenHeight(resolution.height)
    {}
    ~ScreenPercentage(){}

    float toPixelsOnX(const float percentage){return std::floor(static_cast<float>(screenWidth) * percentage / 100.f);}
    float toPixelsOnY(const float percentage){return std::floor(static_cast<float>(screenHeight) * percentage / 100.f);}
private:
    uint screenWidth;
    uint screenHeight;
};

class ButtonBuilder
{
public:
    ButtonBuilder(){}
    virtual ~ButtonBuilder(){}

    virtual ButtonBuilder& withTextContent(const sf::Text&) = 0;
    virtual ButtonBuilder& atPosition(const float, const float) = 0;
    virtual ButtonBuilder& withSize(const float, const float) = 0;
    virtual std::unique_ptr<Button> build() = 0;
};

class MenuButtonBuilder : public ButtonBuilder
{
public:
    MenuButtonBuilder(const sf::VideoMode&);
    virtual ~MenuButtonBuilder(){}
 
    virtual MenuButtonBuilder& withTextContent(const sf::Text& text) override;
    virtual MenuButtonBuilder& atPosition(const float x, const float y) override;
    virtual MenuButtonBuilder& withSize(const float x, const float y) override;
    virtual std::unique_ptr<Button> build() override;

private:
    sf::VideoMode screenResolution;
    std::optional<sf::Text> textContent;
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f size{0.f, 0.f};
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
};

}