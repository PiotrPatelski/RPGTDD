#pragma once
#include <SFML/Graphics.hpp>
#include <ButtonEventHandler.hpp>
#include <ButtonActions.hpp>

namespace Gui
{

sf::Vector2f calculateTextPosOnBackground(const sf::Shape&, const sf::Text&);

struct EventColor
{
    sf::Color text;
    sf::Color background;
    sf::Color outline;
};

class IButton
{
public:
    IButton(){}
    virtual ~IButton(){}

    virtual const bool isPressed() const = 0;
    virtual void update(const sf::Vector2i&) = 0;

    //TODO: MOVE METHOD TO SEPARATE INTERFACE
    virtual Events::StateChangeAction getAction() const = 0;
    //
    virtual sf::Text getTextContent() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual sf::Font getFont() const = 0;
    virtual sf::RectangleShape getBackground() const = 0;
};

class MainMenuButton : public IButton
{
public:
    MainMenuButton(
        const sf::Vector2f&,
        const sf::Vector2f&,
        const std::string&,
        const sf::Font&,
        const uint,
        const EventColor&,
        const EventColor&,
        const EventColor&,
        std::unique_ptr<Events::IButtonEventHandler>,
        const Events::StateChangeAction&);
    virtual ~MainMenuButton(){}

    virtual inline const bool isPressed() const override {return active;}
    virtual void update(const sf::Vector2i&) override;

    virtual Events::StateChangeAction getAction() const override {return action;}

    virtual inline sf::Text getTextContent() const override {return textContent;}
    virtual inline sf::Vector2f getPosition() const override {return position;}
    virtual inline sf::Vector2f getSize() const override {return size;}
    virtual inline sf::Font getFont() const override {return *textContent.getFont();}
    virtual inline sf::RectangleShape getBackground() const override {return background;}
private:
    void initText(const uint);
    void initBackground();
    void setColor(const EventColor&);

    bool active{false};
    sf::Text textContent;
    sf::RectangleShape background;
    sf::Vector2f position;
    sf::Vector2f size;
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
    std::unique_ptr<Events::IButtonEventHandler> eventHandler;
    Events::StateChangeAction action;
};

}