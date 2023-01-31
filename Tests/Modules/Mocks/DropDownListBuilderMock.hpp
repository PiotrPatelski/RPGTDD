#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <DropDownListBuilder.hpp>

namespace Gui
{

using ::testing::Test;

class DropDownListBuilderMock : public DropDownListBuilder
{
public:
    MOCK_METHOD(DropDownListBuilder&, withTextContent, (const sf::Text&), (override));
    MOCK_METHOD(std::unique_ptr<DropDownList>, build, (std::unique_ptr<IButton>), (override));
};

}