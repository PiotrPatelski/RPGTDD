#include <Window.h>


namespace Core
{

Window::Window()
: window(nullptr)
{
    std::cout << "Opening window..." << std::endl;
    
}

void Window::open()
{
    std::cout << "Opening window..." << std::endl;
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "SFML window");
}

void Window::handleSfmlEvents(sf::Event event)
{
    if(window == nullptr)
        throw std::runtime_error(std::string("ERROR::called handleSfmlEvents() on inactive window, ABORTING..."));
    while(window and window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();
    }
}

void Window::close()
{
    if(window == nullptr)
        throw std::runtime_error(std::string("ERROR::called close() on inactive window, ABORTING..."));
    std::cout << "Closing window..." << std::endl;
    window->close();
};

}