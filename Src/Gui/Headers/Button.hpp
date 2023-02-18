#pragma once
#include <SFML/Graphics.hpp>
#include <ButtonEventHandler.hpp>
#include <StateActions.hpp>

namespace Gui
{

sf::Vector2f calculateTextPosOnBackground(const sf::Shape&, const sf::Text&);

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
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual std::optional<sf::Font> getFont() const = 0;
    virtual sf::RectangleShape getBackground() const = 0;
    virtual std::unique_ptr<Button> clone(const std::optional<sf::Text>, const sf::Vector2f&) = 0;
};

class MainMenuButton : public Button
{
public:
    MainMenuButton(
        const sf::Vector2f&,
        const sf::Vector2f&,
        const std::optional<sf::Text>,
        const EventColor&,
        const EventColor&,
        const EventColor&,
        std::unique_ptr<Events::IButtonEventHandler>);

    virtual ~MainMenuButton(){}

    virtual inline const bool isPressed() const override {return active;}
    virtual void update(const sf::Vector2i&) override;

    virtual inline std::optional<sf::Text> getTextContent() const override {return textContent;}
    virtual inline sf::Vector2f getPosition() const override {return position;}
    virtual inline sf::Vector2f getSize() const override {return size;}
    virtual std::optional<sf::Font> getFont() const override;
    virtual inline sf::RectangleShape getBackground() const override {return background;}
    virtual std::unique_ptr<Button> clone(const std::optional<sf::Text>, const sf::Vector2f&) override;

private:
    void initText();
    void initBackground();
    void setColor(const EventColor&);

    bool active{false};

    sf::RectangleShape background;
    sf::Vector2f position;
    sf::Vector2f size;
    std::optional<sf::Text> textContent;
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
    std::unique_ptr<Events::IButtonEventHandler> eventHandler;
};

struct ActionButton
{
    std::unique_ptr<Gui::Button> object;
    Events::StateAction action;
};

}