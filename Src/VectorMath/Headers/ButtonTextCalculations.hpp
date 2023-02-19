#include <SFML/Graphics.hpp>

namespace Types
{
class Background;
}

namespace VectorMath
{

sf::Vector2f calculateTextPosOnBackground(const Types::Background&, const sf::FloatRect&);

uint calculateFontSize(const sf::Vector2f&);

}