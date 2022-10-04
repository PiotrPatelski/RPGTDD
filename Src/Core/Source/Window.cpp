#include <Window.h>


namespace Core
{

Window::Window(const sf::VideoMode& videoMode, const sf::String& title)
{
    this->window = std::make_unique<sf::RenderWindow>(videoMode, title);
}
}