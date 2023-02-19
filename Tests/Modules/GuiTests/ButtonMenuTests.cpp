#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonMenu.hpp>
#include <Background.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>
#include <ButtonBuilderMock.hpp>

namespace Gui
{

using namespace ::testing;

struct ButtonMenuTest : public testing::Test
{
    ButtonMenuTest()
    {
        button1 = std::make_unique<NiceMock<ButtonMock>>();
        button2 = std::make_unique<NiceMock<ButtonMock>>();
        button3 = std::make_unique<NiceMock<ButtonMock>>();
        ON_CALL(*button1, getBackground()).WillByDefault(Return(background));
        ON_CALL(*button1, getTextContent()).WillByDefault(Return(buttonText));
        ON_CALL(*button2, getBackground()).WillByDefault(Return(background));
        ON_CALL(*button2, getTextContent()).WillByDefault(Return(buttonText));
        ON_CALL(*button3, getBackground()).WillByDefault(Return(background));
        ON_CALL(*button3, getTextContent()).WillByDefault(Return(buttonText));
    }
    const sf::VideoMode resolution{1920, 1080};
    const VectorMath::ScreenPercentagePoint size{resolution, sf::Vector2f{30.f, 70.f}};
    const VectorMath::ScreenPercentagePoint position{resolution, sf::Vector2f{480.f, 480.f}};
    std::unique_ptr<NiceMock<ButtonMock>> button1;
    std::unique_ptr<NiceMock<ButtonMock>> button2;
    std::unique_ptr<NiceMock<ButtonMock>> button3;
    NiceMock<::Types::WindowMock> window;
    ::Types::Background background{position, size};
    const sf::Text buttonText{"test", sf::Font{}};
};

TEST_F(ButtonMenuTest, buttonMenuWillUpdateAllAddedActionButtonsWithMousePosition)
{
    const auto mousePosition = sf::Vector2i{3, 3};
    EXPECT_CALL(*button1, update(Eq(mousePosition)));
    EXPECT_CALL(*button2, update(Eq(mousePosition)));
    EXPECT_CALL(*button3, update(Eq(mousePosition)));

    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    buttons.push_back({std::move(button2), std::monostate{}});
    buttons.push_back({std::move(button3), std::monostate{}});

    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));
    sut->update(mousePosition);
}

TEST_F(ButtonMenuTest, buttonMenuWillDrawBackgroundsOfAllAddedActionButtons)
{
    EXPECT_CALL(*button1, getBackground()).WillOnce(Return(background));
    EXPECT_CALL(*button2, getBackground()).WillOnce(Return(background));
    EXPECT_CALL(*button3, getBackground()).WillOnce(Return(background));

    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    buttons.push_back({std::move(button2), std::monostate{}});
    buttons.push_back({std::move(button3), std::monostate{}});

    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));
    sut->drawTo(window);
}

TEST_F(ButtonMenuTest, buttonMenuWillDrawTextsOfAllAddedActionButtons)
{
    EXPECT_CALL(*button1, getTextContent()).WillOnce(Return(buttonText));
    EXPECT_CALL(*button2, getTextContent()).WillOnce(Return(buttonText));
    EXPECT_CALL(*button3, getTextContent()).WillOnce(Return(buttonText));

    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    buttons.push_back({std::move(button2), std::monostate{}});
    buttons.push_back({std::move(button3), std::monostate{}});

    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));
    sut->drawTo(window);
}

TEST_F(ButtonMenuTest, windowWillDrawButtonMenuBackgroundAndText)
{
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(2);
    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::vector<ActionButton>{});
    sut->drawTo(window);
}

TEST_F(ButtonMenuTest, windowWillDrawButtonMenuBackgroundTextAndSectionBackgroundWhenNoTextIsReturnedFromSection)
{
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(3);
    EXPECT_CALL(*button1, getTextContent()).WillOnce(Return(std::nullopt));
    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));
    sut->drawTo(window);
}

TEST_F(ButtonMenuTest, windowWillDrawButtonMenuBackgroundTextSectionBackgroundAndSectionTextWhenTextIsReturnedFromSection)
{
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(4);
    EXPECT_CALL(*button1, getTextContent()).WillOnce(Return(buttonText));
    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));
    sut->drawTo(window);
}

TEST_F(ButtonMenuTest, buttonMenuWillGetNulloptWhenNoSectionsArePressed)
{
    EXPECT_CALL(*button1, isPressed()).WillOnce(Return(false));
    EXPECT_CALL(*button2, isPressed()).WillOnce(Return(false));
    EXPECT_CALL(*button3, isPressed()).WillOnce(Return(false));

    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    buttons.push_back({std::move(button2), std::monostate{}});
    buttons.push_back({std::move(button3), std::monostate{}});

    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));

    EXPECT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(ButtonMenuTest, buttonMenuWillReturnActionOfFirstPressedSection)
{
    EXPECT_CALL(*button1, isPressed()).WillOnce(Return(false));
    EXPECT_CALL(*button2, isPressed()).WillOnce(Return(true));
    EXPECT_CALL(*button3, isPressed()).Times(0);

    std::vector<ActionButton> buttons;
    buttons.push_back({std::move(button1), std::monostate{}});
    buttons.push_back({std::move(button2), std::monostate{}});
    buttons.push_back({std::move(button3), std::monostate{}});

    auto sut = std::make_unique<ButtonMenu>(
        sf::Text("test", sf::Font{}),
        background,
        std::move(buttons));

    EXPECT_NE(sut->getActiveAction(), std::nullopt);
}

}