#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Config.h>

namespace Core
{

class IWindow
{
public:
    IWindow(){}
    virtual ~IWindow(){}

    virtual bool isActive() = 0;
    virtual bool isCurrentlyFocused() = 0;
    virtual void openWithSettings(const GraphicsConfig&) = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
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
    virtual void openWithSettings(const GraphicsConfig&);
    virtual void clear() override {window->clear();}
    virtual void display() override {window->display();}
    virtual void handleSfmlEvents(sf::Event) override;
    virtual void close() override;
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}