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
        sut = std::make_unique<DropDownListBuilder>();
        button = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*button, getPosition()).WillByDefault
            (Return(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f{0, 0})));
        ON_CALL(*button, getSize()).WillByDefault
            (Return(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f{0, 0})));
    }
    const sf::VideoMode resolution{1920, 1080};
    std::unique_ptr<ButtonListBuilder> sut;
    std::unique_ptr<NiceMock<ButtonMock>> button;
};

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesButtonListWithDefaultValues)
{
    auto dropDownList = sut->build();
    ASSERT_EQ(dropDownList->getTextContent().getString(), "");
    ASSERT_EQ(dropDownList->getActiveAction(), std::nullopt);
    ASSERT_FALSE(dropDownList->isActive());
}

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesButtonListWithGivenTextContent)
{
    sf::Text text("TestButtonList", sf::Font{});
    auto dropDownList = sut->withTriggerButton(std::move(button)).withTextContent(text).build();
    ASSERT_EQ(dropDownList->getTextContent().getString(), "TestButtonList");
}

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesButtonListAtGivenPosition)
{
    const VectorMath::ScreenPercentagePoint position(resolution, {10.f, 10.f});
    EXPECT_CALL(*button, getPosition()).WillOnce(Return(position));
    auto buttonMenu = sut->withTriggerButton(std::move(button)).build();
    ASSERT_EQ(buttonMenu->getPosition().value(), position.value());
}

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesButtonListWithGivenSize)
{
    const VectorMath::ScreenPercentagePoint size(resolution, {10.f, 10.f});
    EXPECT_CALL(*button, getSize()).WillOnce(Return(size));
    auto buttonMenu = sut->withTriggerButton(std::move(button)).build();
    ASSERT_EQ(buttonMenu->getSize().value(), size.value());
}

TEST_F(DropDownListBuilderTest, dropDownListBuilderCreatesButtonListWithSectionsClonedFromTriggerButtonAndPositionRelativeToPrevious)
{
    const VectorMath::ScreenPercentagePoint size(resolution, {10.f, 10.f});
    const VectorMath::ScreenPercentagePoint position(resolution, {10.f, 10.f});
    sf::Text buttonText;
    buttonText.setString("Test");
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    auto testButton2 = std::make_unique<NiceMock<ButtonMock>>();

    EXPECT_CALL(*button, getSize()).WillOnce(Return(size));
    EXPECT_CALL(*button, getPosition()).WillOnce(Return(position));
    EXPECT_CALL(*testButton1, getSize()).WillOnce(Return(size));
    EXPECT_CALL(*testButton1, getPosition()).WillOnce(Return(position));
    EXPECT_CALL(*testButton2, getSize()).WillOnce(Return(size));
    EXPECT_CALL(*testButton2, getPosition()).WillOnce(Return(position));
    EXPECT_CALL(*button, clone(Optional(Property(&sf::Text::getString, StrEq("Test"))), _)).
        Times(3).
        WillOnce(Return(ByMove(std::move(testButton1)))).
        WillOnce(Return(ByMove(std::move(testButton2)))).
        WillOnce(Return(ByMove(std::make_unique<NiceMock<ButtonMock>>())));

    auto buttonMenu = sut->withTriggerButton(std::move(button)).
        withSection(buttonText, std::monostate{}).
        withSection(buttonText, std::monostate{}).
        withSection(buttonText, std::monostate{}).
        build();
}

}