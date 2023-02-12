#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonListBuilder.hpp>

namespace Gui
{

using ::testing::Test;

class ButtonListBuilderMock : public ButtonListBuilder
{
public:
    MOCK_METHOD(ButtonListBuilder&, withTextContent, (const sf::Text&), (override));
    MOCK_METHOD(std::unique_ptr<ButtonList>, build, (std::unique_ptr<IButton>), (override));
};

}