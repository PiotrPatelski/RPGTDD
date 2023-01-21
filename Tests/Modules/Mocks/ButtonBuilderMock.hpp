#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonBuilder.hpp>

namespace Gui
{

using ::testing::Test;

class ButtonBuilderMock : public IButtonBuilder
{
public:
    MOCK_METHOD(IButtonBuilder&, withTextContent, (const std::string&), (override));
    MOCK_METHOD(IButtonBuilder&, atPosition, (const float, const float), (override));
    MOCK_METHOD(IButtonBuilder&, withSize, (const float, const float), (override));
    MOCK_METHOD(IButtonBuilder&, withFont, (const std::shared_ptr<sf::Font>), (override));
    MOCK_METHOD(std::shared_ptr<IButton>, build, (), (override));
};

}