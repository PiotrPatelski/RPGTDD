#pragma once
#include <SFML/Graphics.hpp>

namespace Gui
{

class IButton
{
public:
    IButton(){}
    virtual ~IButton(){}

    virtual std::string getTextContent() = 0;
    virtual sf::Vector2f getPosition() = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual sf::Font getFont() =0;
};

class MainMenuButton : public IButton
{
public:
    MainMenuButton(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Font&);
    virtual ~MainMenuButton(){}

    virtual std::string getTextContent() override {return textContent.getString();}
    virtual sf::Vector2f getPosition() override {return position;}
    virtual sf::Vector2f getSize() override {return size;}
    virtual sf::Font getFont() override {return *textContent.getFont();}
private:
    sf::Text textContent;
    sf::Vector2f position;
    sf::Vector2f size;
};

}