#include <TileBuilder.hpp>
#include <Tile.hpp>

namespace Tiles
{

DefaultTileBuilder::DefaultTileBuilder(const sf::Texture* textureSheet, const std::vector<std::string>& tileIds)
: tileTextureSheet{textureSheet}
{
    std::cout<<"Pioter "<<(textureSheet->getSize().x)<<" "<<(textureSheet->getSize().y)<<std::endl;
}

std::unique_ptr<Tile> DefaultTileBuilder::build()
{
    auto tile = std::make_unique<NormalTile>(tileTextureSheet);
    tile->setPosition(currentPosition);
    return std::move(tile);
}

DefaultTileBuilder& DefaultTileBuilder::atPosition(const sf::Vector2i& position)
{
    currentPosition = position;
    return *this;
}

}