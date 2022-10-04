#include <WindowBuilder.h>

namespace Core
{

Window WindowBuilder::build()
{ 
    return Window(sf::VideoMode(800, 600), "SFML window");
}

}