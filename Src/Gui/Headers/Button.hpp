#pragma once
#include <SFML/Graphics.hpp>

namespace Gui
{

sf::Vector2f calculateTextPosOnBackground(const sf::Shape&, const sf::Text&);

struct EventColor
{
    sf::Color idle;
    sf::Color hover;
    sf::Color active;
};

class IButton
{
public:
    IButton(){}
    virtual ~IButton(){}

    virtual void update(const sf::Vector2i&) = 0;

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
        const uint characterSize,
        const EventColor&,
        const EventColor&,
        const EventColor&);
    virtual ~MainMenuButton(){}

    virtual void update(const sf::Vector2i&) override;

    virtual inline sf::Text getTextContent() const override {return textContent;}
    virtual inline sf::Vector2f getPosition() const override {return position;}
    virtual inline sf::Vector2f getSize() const override {return size;}
    virtual inline sf::Font getFont() const override {return *textContent.getFont();}
    virtual inline sf::RectangleShape getBackground() const override {return background;}
private:
    void initText(const uint);
    void initBackground();
    sf::Text textContent;
    sf::RectangleShape background;
    sf::Vector2f position;
    sf::Vector2f size;
    EventColor textColors;
    EventColor backgroundColors;
    EventColor outlineColors;
};

}