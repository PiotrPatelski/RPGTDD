#include <TileBuilder.hpp>
#include <Tile.hpp>

namespace Tiles
{

DefaultTileBuilder::DefaultTileBuilder(const sf::Texture* textureSheet, const std::vector<std::string>& tileIds, const uint tileBoxSize)
: tileTextureSheet{textureSheet},
  tileBoxSize{static_cast<int>(tileBoxSize)}
{
    std::cout<< "DefaultTileBuilder:: init" <<std::endl;
    mapIdsToTextureFields(tileIds, textureSheet->getSize());
    std::cout<< "DefaultTileBuilder:: init done" <<std::endl;
}

std::unique_ptr<Tile> DefaultTileBuilder::build(const std::string& tileId)
{
    //TODO this .at throws
    const sf::Sprite sprite(*tileTextureSheet, tileTextures.at(tileId));
    auto tile = std::make_unique<NormalTile>(sprite);
    tile->setPosition(currentPosition);
    return std::move(tile);
}

DefaultTileBuilder& DefaultTileBuilder::atPosition(const sf::Vector2i& position)
{
    currentPosition = position;
    return *this;
}

void DefaultTileBuilder::mapIdsToTextureFields(const std::vector<std::string>& tileIds, const sf::Vector2u& sheetSize)
{
    uint xIndex{0};
    uint yIndex{0};

    for (auto id : tileIds)
    {
        tileTextures.emplace(id, sf::IntRect(xIndex, yIndex, tileBoxSize, tileBoxSize));
        if(xIndex < sheetSize.x)
        {
            xIndex += tileBoxSize;
        }
        else
        {
            xIndex = 0;
            yIndex += tileBoxSize;
        }
    }
}

}