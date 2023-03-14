#pragma once
#include <SFML/Graphics.hpp>

namespace Events
{

class MouseEventListener
{
public:
    MouseEventListener(){}
    virtual ~MouseEventListener(){}

    virtual bool isPressed() const = 0;
};

class SimpleMouseEventListener : public MouseEventListener
{
public:
    SimpleMouseEventListener(){}
    virtual ~SimpleMouseEventListener(){}

    virtual bool isPressed() const override {return sf::Mouse::isButtonPressed(sf::Mouse::Left);}
};

}