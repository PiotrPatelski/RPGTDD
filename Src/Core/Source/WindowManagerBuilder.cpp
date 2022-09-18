#include <WindowManagerBuilder.h>

namespace Core
{

std::unique_ptr<IWindowManager> WindowManagerBuilder::build()
{ 
    return std::make_unique<WindowManager>(sf::VideoMode(800, 600), "SFML window");
}

}