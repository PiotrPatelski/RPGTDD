#pragma once
#include <SFML/Graphics.hpp>
#include <MouseEventListener.hpp>
#include <StateActions.hpp>
#include <PixelsPoint.hpp>
#include <Background.hpp>

namespace VectorMath
{
class ScreenPercentagePoint;
}

namespace Gui
{

struct EventColor
{
    sf::Color text;
    sf::Color background;
    sf::Color outline;
};

class Button
{
public:
    Button(){}
    virtual ~Button(){}

    virtual const bool isPressed() const = 0;
    virtual void update(const sf::Vector2i&) = 0;

    virtual std::optional<sf::Text> getTextContent() const = 0;
    virtual void setTextContent(const sf::Text&) = 0;
    virtual VectorMath::ScreenPercentagePoint getPosition() const = 0;
    virtual VectorMath::ScreenPercentagePoint getSize() const = 0;
    virtual std::optional<sf::Font> getFont() const = 0;
    virtual Types::Background getBackground() const = 0;
    virtual std::unique_ptr<Button> clone(const std::optional<sf::Text>, const VectorMath::ScreenPercentagePoint&) = 0;
};

class MainMenuButton : public Button
{
public:
    MainMenuButton(
        const VectorMath::ScreenPercentagePoint&,
        const VectorMath::ScreenPercentagePoint&,
        const std::optional<sf::Text>,
        const EventColor&,
        const EventColor&,
        const EventColor&,
        std::unique_ptr<Events::MouseEventListener>);

    virtual ~MainMenuButton(){}

    virtual inline const bool isPressed() const override {return active;}
    virtual void update(const sf::Vector2i&) override;

    virtual void setTextContent(const sf::Text& text) override;
    virtual inline std::optional<sf::Text> getTextContent() const override {return textContent;}
    virtual inline VectorMath::ScreenPercentagePoint getPosition() const override;
    virtual inline VectorMath::ScreenPercentagePoint getSize() const override;
    virtual std::optional<sf::Font> getFont() const override;
    virtual inline Types::Background getBackground() const override {return background;}
    virtual std::unique_ptr<Button> clone(const std::optional<sf::Text>, const VectorMath::ScreenPercentagePoint&) override;

private:
    void initText();
    void initBackground();
    void setColor(const EventColor&);

    bool active{false};

    Types::Background background;
    std::optional<sf::Text> textContent;
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
    std::unique_ptr<Events::MouseEventListener> EventListener;
};

struct ActionButton
{
    std::unique_ptr<Gui::Button> object;
    Events::StateAction action;
};

}