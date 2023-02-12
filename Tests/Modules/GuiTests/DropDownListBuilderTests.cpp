#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <DropDownListBuilder.hpp>
#include <ButtonMock.hpp>

namespace Gui
{

using namespace ::testing;

struct DropDownListBuilderTest : public testing::Test
{
    DropDownListBuilderTest()
    {
        sut = std::make_unique<MenuDropDownListBuilder>();
        button = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*button, getPosition()).WillByDefault(Return(sf::Vector2f{0, 0}));
    }
    std::unique_ptr<DropDownListBuilder> sut;
    std::unique_ptr<NiceMock<ButtonMock>> button;
};

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesDropDownListWithDefaultValues)
{
    auto dropDownList = sut->build(std::move(button));
    ASSERT_EQ(dropDownList->getTextContent().getString(), "");
    ASSERT_EQ(dropDownList->getActiveAction(), std::nullopt);
    ASSERT_FALSE(dropDownList->isActive());
}

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesDropDownListWithGivenTextContent)
{
    sf::Text text("TestDropDownList", sf::Font{});
    auto dropDownList = sut->withTextContent(text).build(std::move(button));
    ASSERT_EQ(dropDownList->getTextContent().getString(), "TestDropDownList");
}

}