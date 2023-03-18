#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Config.hpp>

namespace Types
{

class Window
{
public:
    Window();
    virtual ~Window(){}

    virtual inline bool isActive() const {return window != nullptr and window->isOpen();}
    virtual inline bool isCurrentlyFocused() const {return window->hasFocus();}
    virtual void openWithSettings(const FileMgmt::GraphicsConfig&);
    virtual inline sf::Vector2i getMousePosition() const {return sf::Mouse::getPosition(*window);}
    virtual void clear() {window->clear();}
    virtual void draw(const sf::Drawable& object) {window->draw(object);}
    virtual void display() {window->display();}
    virtual void handleSfmlEvents(sf::Event);
    virtual void close();
private:
    std::unique_ptr<sf::RenderWindow> window;
};

}