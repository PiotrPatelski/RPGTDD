#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonBuilder.hpp>

namespace Gui
{

using ::testing::Test;

class ButtonBuilderMock : public ButtonBuilder
{
public:
    MOCK_METHOD(ButtonBuilder&, withTextContent, (const sf::Text&), (override));
    MOCK_METHOD(ButtonBuilder&, atPosition, (const VectorMath::ScreenPercentagePoint&), (override));
    MOCK_METHOD(ButtonBuilder&, withSize, (const VectorMath::ScreenPercentagePoint&), (override));
    MOCK_METHOD(std::unique_ptr<Button>, build, (), (override));
};

}