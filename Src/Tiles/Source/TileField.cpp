#include <TileField.hpp>
#include <Tile.hpp>

namespace Tiles
{

constexpr uint AMOUNT_OF_LAYERS{3};

TileField::TileField(const sf::Vector2i& position)
: fieldPosition{position}
{
    layers.resize(AMOUNT_OF_LAYERS);
}

sf::Vector2i TileField::getPosition() const
{
    return {0,0};
}

bool TileField::isEmpty() const
{
    return std::all_of(layers.cbegin(), layers.cend(), 
        [](const auto& layer){return layer == nullptr;});
}

bool TileField::isFull() const
{
    return std::none_of(layers.cbegin(), layers.cend(), 
        [](const auto& layer){return layer == nullptr;});
}

void TileField::pushTile(std::unique_ptr<Tile> tile)
{
    auto firstEmptyIndex = std::find_if(layers.begin(), layers.end(),
        [](const auto& layer){return layer == nullptr;});
    if(firstEmptyIndex != std::end(layers))
    {
        tile->setPosition(fieldPosition);
        *firstEmptyIndex = std::move(tile);
    }
}

void TileField::popTile()
{
    auto firstEmptyIndex = std::find_if_not(layers.begin(), layers.end(),
        [](const auto& layer){return layer == nullptr;});
    if(firstEmptyIndex != std::end(layers))
        firstEmptyIndex->reset();
}

void TileField::drawTo(Types::Window& window)
{
    for(auto& layer : layers)
    {
        if(layer)
            layer->drawTo(window);
    }
}

TileField::TileField(TileField&& other)
: layers(std::move(other.layers)),
  fieldPosition{other.fieldPosition}
{}

TileField& TileField::operator=(TileField&& other)
{
    assert(layers.size() == other.layers.size());
    layers = std::move(other.layers);
    fieldPosition = other.fieldPosition;
    return *this;
}

}