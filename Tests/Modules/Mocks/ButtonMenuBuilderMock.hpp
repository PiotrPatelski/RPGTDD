#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonMenuBuilder.hpp>

namespace Gui
{

using ::testing::Test;

class ButtonMenuBuilderMock : public ButtonMenuBuilder
{
public:
    MOCK_METHOD(ButtonMenuBuilder&, withTextContent, (const sf::Text&), (override));
    MOCK_METHOD(ButtonMenuBuilder&, withTriggerButton, (std::unique_ptr<Button>), (override));
    MOCK_METHOD(ButtonMenuBuilder&, withSection, (const std::optional<sf::Text>, Events::StateAction), (override));
    MOCK_METHOD(ButtonMenuBuilder&, atPosition, (const VectorMath::ScreenPercentagePoint&), (override));
    MOCK_METHOD(ButtonMenuBuilder&, withSize, (const VectorMath::ScreenPercentagePoint&), (override));
    MOCK_METHOD(std::unique_ptr<ButtonList>, build, (), (override));
};

}