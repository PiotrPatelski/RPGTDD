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
    TileMapMock()
        : TileMap(0.f, 0, 0){}
    MOCK_METHOD(bool, isValidPosition, (const sf::Vector2i&), (const, override));
    MOCK_METHOD(bool, isEmptyAt, (const sf::Vector2i&), (const, override));
    MOCK_METHOD(void, addTile, (std::unique_ptr<Tile>), (override));
    MOCK_METHOD(void, removeTile, (const sf::Vector2i&), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, drawTo, (::Types::Window&), (override));
};

}