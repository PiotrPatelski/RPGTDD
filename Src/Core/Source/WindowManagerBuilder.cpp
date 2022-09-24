#include <WindowManagerBuilder.h>

namespace Core
{

WindowManager WindowManagerBuilder::build()
{ 
    return WindowManager(sf::VideoMode(800, 600), "SFML window");
}

}