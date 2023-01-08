#pragma once
#include <SFML/Graphics.hpp>

namespace Events
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

    virtual bool isPressed() const override {return sf::Mouse::isButtonPressed(sf::Mouse::Left);}
};

}