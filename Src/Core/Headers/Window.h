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
    virtual void open() = 0;
    virtual void clear() = 0;
    virtual void displayWindow() = 0;
    virtual void handleSfmlEvents(sf::Event) = 0;
    virtual void close() = 0;
};

class Window : public IWindow
{
public:
    Window();
    virtual ~Window(){}

    virtual bool isActive() override {return window != nullptr and window->isOpen();}
    virtual bool isCurrentlyFocused() override {return window->hasFocus();}
    virtual void open();
    virtual void clear() override {window->clear();}
    virtual void displayWindow() override {window->display();}
    virtual void handleSfmlEvents(sf::Event) override;
    virtual void close() override;
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}