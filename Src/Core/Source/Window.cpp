#include <Window.h>


namespace Core
{

Window::Window()
: window(nullptr)
{
    std::cout << "Creating window..." << std::endl;
    
}

void Window::openWithSettings(const GraphicsConfig& config)
{
    std::cout << "Opening window..." << std::endl;

    auto isFullscreen = (config.fullscreen) ?
        sf::Style::Fullscreen :
        sf::Style::Titlebar | sf::Style::Close;

    window = std::make_unique<sf::RenderWindow>(
        config.resolution,
        config.gameTitle,
        isFullscreen,
        config.contextSettings);
    window->setFramerateLimit(config.frameRateLimit);
    window->setVerticalSyncEnabled(config.verticalSync);
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

void Window::drawStateOutput(const States::StateOutput& output)
{
    window->draw(output.background);
}

void Window::close()
{
    if(window == nullptr)
        throw std::runtime_error(std::string("ERROR::called close() on inactive window, ABORTING..."));
    std::cout << "Closing window..." << std::endl;
    window->close();
};

}