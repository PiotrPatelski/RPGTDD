#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Tile.hpp>

namespace Tiles
{

using namespace ::testing;

class TileMock : public Tile
{
public:
    MOCK_METHOD(void, drawTo, (::Types::Window&), (override));
    MOCK_METHOD(void, setPosition, (const sf::Vector2i&), (override));
    MOCK_METHOD(sf::Vector2i, getPosition, (), (override, const));
};

}