#include <WindowManager.h>


namespace Core
{

WindowManager::WindowManager(const sf::VideoMode& videoMode, const sf::String& title)
{
    this->window = std::make_unique<sf::RenderWindow>(videoMode, title);
}
}