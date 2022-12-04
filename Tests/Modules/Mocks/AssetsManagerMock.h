#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.h>

namespace Core
{

using ::testing::Test;

class MainMenuAssetsManagerMock : public IAssetsManager
{
public:
   MOCK_METHOD(void, fetchTextureFromFile, (), (override));
   MOCK_METHOD(const sf::Texture&, getTexture, (), (override));
   MOCK_METHOD(void, fetchFontFromFile, (), (override));
   MOCK_METHOD(const sf::Font&, getFont, (), (override));
};

}