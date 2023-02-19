#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonMenuBuilder.hpp>
#include <ButtonMock.hpp>

namespace Gui
{

using namespace ::testing;

struct ButtonMenuBuilderTest : public testing::Test
{
    ButtonMenuBuilderTest()
    {
        sut = std::make_unique<ButtonMenuBuilder>();
        button = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*button, getPosition()).WillByDefault
            (Return(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f{0, 0})));
    }
    const sf::VideoMode resolution{1920, 1080};
    std::unique_ptr<ButtonMenuBuilder> sut;
    std::unique_ptr<NiceMock<ButtonMock>> button;
};

TEST_F(ButtonMenuBuilderTest, buttonMenuBuilderCreatesButtonListWithDefaultValues)
{
    auto buttonMenu = sut->build();
    ASSERT_EQ(buttonMenu->getTextContent().getString(), "");
    ASSERT_EQ(buttonMenu->getActiveAction(), std::nullopt);
    ASSERT_FALSE(buttonMenu->isActive());
}

TEST_F(ButtonMenuBuilderTest, buttonMenuBuilderCreatesButtonListWithGivenTextContent)
{
    const sf::Text text("TestButtonList", sf::Font{});
    auto buttonMenu = sut->withTextContent(text).build();
    ASSERT_EQ(buttonMenu->getTextContent().getString(), "TestButtonList");
}

TEST_F(ButtonMenuBuilderTest, buttonMenuBuilderCreatesButtonListAtGivenPosition)
{
    const VectorMath::ScreenPercentagePoint position(resolution, {10.f, 10.f});
    auto buttonMenu = sut->atPosition(position).build();
    ASSERT_EQ(buttonMenu->getPosition().value(), position.value());
}

TEST_F(ButtonMenuBuilderTest, buttonMenuBuilderCreatesButtonListWithGivenSize)
{
    const VectorMath::ScreenPercentagePoint size(resolution, {10.f, 10.f});
    auto buttonMenu = sut->withSize(size).build();
    ASSERT_EQ(buttonMenu->getSize().value(), size.value());
}

}