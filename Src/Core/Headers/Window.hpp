#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Config.hpp>

namespace Core
{

class IWindow
{
public:
    IWindow(){}
    virtual ~IWindow(){}

    virtual bool isActive() = 0;
    virtual bool isCurrentlyFocused() = 0;
    virtual void openWithSettings(const FileMgmt::GraphicsConfig&) = 0;
    virtual sf::Vector2i getMousePosition() const = 0;
    virtual void clear() = 0;
    virtual void draw(const sf::Drawable&) = 0;
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
    virtual void openWithSettings(const FileMgmt::GraphicsConfig&);
    virtual sf::Vector2i getMousePosition() const override {return sf::Mouse::getPosition(*window);}
    virtual void clear() override {window->clear();}
    virtual void draw(const sf::Drawable& object) {window->draw(object);}
    virtual void display() override {window->display();}
    virtual void handleSfmlEvents(sf::Event) override;
    virtual void close() override;
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}