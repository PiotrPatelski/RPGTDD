#pragma once
#include <SFML/Graphics.hpp>

namespace Events
{

class MouseEventListener
{
public:
    MouseEventListener(){}
    virtual ~MouseEventListener(){}

    virtual bool isLeftPressed() const {return sf::Mouse::isButtonPressed(sf::Mouse::Left);}
    virtual bool isRightPressed() const = 0;
};

class ButtonMouseEventListener : public MouseEventListener
{
public:
    ButtonMouseEventListener(){}
    virtual ~ButtonMouseEventListener(){}

    virtual bool isRightPressed() const override {return false;}
};

class ScenarioMouseEventListener : public MouseEventListener
{
public:
    ScenarioMouseEventListener(){}
    virtual ~ScenarioMouseEventListener(){}

    virtual bool isRightPressed() const override {return sf::Mouse::isButtonPressed(sf::Mouse::Right);}
};

}