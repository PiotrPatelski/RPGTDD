#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.hpp>

namespace FileMgmt
{

using ::testing::Test;

class MainMenuAssetsManagerMock : public MainMenuAssetsManager
{
public:
   MOCK_METHOD(std::shared_ptr<sf::Texture>, getTexture, (), (override));
   MOCK_METHOD(std::shared_ptr<sf::Font>, getFont, (), (override));
};

}