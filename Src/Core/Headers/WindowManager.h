#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Core
{

class IWindowManager
{
public:
    IWindowManager(){}
    virtual ~IWindowManager(){}

    virtual bool isWindowActive() = 0;  
};

class WindowManager : public IWindowManager
{
public:
    WindowManager(const sf::VideoMode&, const sf::String&);
    virtual ~WindowManager(){}

    virtual bool isWindowActive(){return window->isOpen();}
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}