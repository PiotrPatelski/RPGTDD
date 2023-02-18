#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <AssetsManager.hpp>

namespace FileMgmt
{

using ::testing::Test;

class AssetsManagerMock : public AssetsManager
{
public:
   MOCK_METHOD((const sf::Texture*), getTexture, (const std::string&), (const, override));
   MOCK_METHOD((const sf::Font&), getFont, (const std::string&), (const, override));
};

}