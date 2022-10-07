#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Core
{

class IWindow
{
public:
    IWindow(){}
    virtual ~IWindow(){}

    virtual bool isActive() = 0;
    virtual bool isCurrentlyFocused() = 0;
    virtual void clear() = 0;
    virtual void displayWindow() = 0;
    virtual void handleSfmlEvents(sf::Event) = 0;
};

class Window : public IWindow
{
public:
    Window(const sf::VideoMode&, const sf::String&);
    virtual ~Window(){}

    virtual bool isActive(){return window->isOpen();}
    virtual bool isCurrentlyFocused(){return window->hasFocus();}
    virtual void clear(){window->clear();}
    virtual void displayWindow(){window->display();}
    virtual void handleSfmlEvents(sf::Event) override;
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}