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
    virtual void clearWindow() = 0;
    virtual void displayWindow() = 0;
};

class WindowManager : public IWindowManager
{
public:
    WindowManager(const sf::VideoMode&, const sf::String&);
    virtual ~WindowManager(){}

    virtual bool isWindowActive(){return window->isOpen();}
    virtual void clearWindow(){window->clear();}
    virtual void displayWindow(){window->display();}
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}