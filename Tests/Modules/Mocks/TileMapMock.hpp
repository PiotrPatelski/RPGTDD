#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileMap.hpp>
#include <Tile.hpp>

namespace Tiles
{

using namespace ::testing;

class TileMapMock : public TileMap
{
public:
    MOCK_METHOD(void, addTile, (std::unique_ptr<Tile>), (override));
    MOCK_METHOD(void, removeTile, (const sf::Vector2i&), (override));
};

}