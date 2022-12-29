#pragma once
#include <SFML/Graphics.hpp>

namespace Gui
{

class IButtonEventHandler
{
public:
    IButtonEventHandler(){}
    virtual ~IButtonEventHandler(){}

    virtual bool isPressed() const = 0;
};

class ButtonEventHandler : public IButtonEventHandler
{
public:
    ButtonEventHandler(){}
    virtual ~ButtonEventHandler(){}

    virtual bool isPressed() const {return sf::Mouse::isButtonPressed(sf::Mouse::Left);}
};

}