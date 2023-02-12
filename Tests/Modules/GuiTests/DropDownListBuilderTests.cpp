#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <DropDownListBuilder.hpp>
#include <ButtonMock.hpp>

namespace Gui
{

using namespace ::testing;

struct ButtonListBuilderTest : public testing::Test
{
    ButtonListBuilderTest()
    {
        sut = std::make_unique<DropDownListBuilder>();
        button = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*button, getPosition()).WillByDefault(Return(sf::Vector2f{0, 0}));
    }
    std::unique_ptr<ButtonListBuilder> sut;
    std::unique_ptr<NiceMock<ButtonMock>> button;
};

TEST_F(ButtonListBuilderTest, dropDownListBuilderCreatesButtonListWithDefaultValues)
{
    auto dropDownList = sut->build(std::move(button));
    ASSERT_EQ(dropDownList->getTextContent().getString(), "");
    ASSERT_EQ(dropDownList->getActiveAction(), std::nullopt);
    ASSERT_FALSE(dropDownList->isActive());
}

TEST_F(ButtonListBuilderTest, dropDownListBuilderCreatesButtonListWithGivenTextContent)
{
    sf::Text text("TestButtonList", sf::Font{});
    auto dropDownList = sut->withTextContent(text).build(std::move(button));
    ASSERT_EQ(dropDownList->getTextContent().getString(), "TestButtonList");
}

}