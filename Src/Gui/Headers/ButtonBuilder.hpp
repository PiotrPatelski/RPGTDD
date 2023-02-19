#pragma once

#include <Button.hpp>
#include <StateActions.hpp>
#include <ScreenPercentagePoint.hpp>

namespace Gui
{

class ButtonBuilder
{
public:
    ButtonBuilder(){}
    virtual ~ButtonBuilder(){}

    virtual ButtonBuilder& withTextContent(const sf::Text&) = 0;
    virtual ButtonBuilder& atPosition(const VectorMath::ScreenPercentagePoint&) = 0;
    virtual ButtonBuilder& withSize(const VectorMath::ScreenPercentagePoint&) = 0;
    virtual std::unique_ptr<Button> build() = 0;
};

class MenuButtonBuilder : public ButtonBuilder
{
public:
    MenuButtonBuilder();
    virtual ~MenuButtonBuilder(){}
 
    virtual MenuButtonBuilder& withTextContent(const sf::Text& text) override;
    virtual MenuButtonBuilder& atPosition(const VectorMath::ScreenPercentagePoint&) override;
    virtual MenuButtonBuilder& withSize(const VectorMath::ScreenPercentagePoint&) override;
    virtual std::unique_ptr<Button> build() override;

private:
    std::optional<sf::Text> textContent;
    VectorMath::ScreenPercentagePoint position{sf::VideoMode(1, 1), sf::Vector2f(0.f, 0.f)};
    VectorMath::ScreenPercentagePoint size{sf::VideoMode(1, 1), sf::Vector2f(0.f, 0.f)};
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
};

}