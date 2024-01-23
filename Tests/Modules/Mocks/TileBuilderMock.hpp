#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <TileBuilder.hpp>

namespace Tiles
{

using namespace ::testing;

class TileBuilderMock : public TileBuilder
{
public:
    MOCK_METHOD(std::unique_ptr<Tile>, build, (), (override));
};

}