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
   MOCK_METHOD(std::shared_ptr<sf::Texture>, getTexture, (), (const, override));
   MOCK_METHOD(std::shared_ptr<sf::Font>, getFont, (), (const, override));
};

class GameAssetsManagerMock : public GameAssetsManager
{
public:
   MOCK_METHOD(std::shared_ptr<sf::Texture>, getTexture, (), (const, override));
   MOCK_METHOD(std::shared_ptr<sf::Font>, getFont, (), (const, override));
};

class SettingsAssetsManagerMock : public SettingsAssetsManager
{
public:
   MOCK_METHOD(std::shared_ptr<sf::Texture>, getTexture, (), (const, override));
   MOCK_METHOD(std::shared_ptr<sf::Font>, getFont, (), (const, override));
};

class EditorAssetsManagerMock : public EditorAssetsManager
{
public:
   MOCK_METHOD(std::shared_ptr<sf::Texture>, getTexture, (), (const, override));
   MOCK_METHOD(std::shared_ptr<sf::Font>, getFont, (), (const, override));
};

}