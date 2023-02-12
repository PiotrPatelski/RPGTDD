#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ButtonMenu.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>
#include <ButtonBuilderMock.hpp>

namespace Gui
{

using namespace ::testing;

struct ButtonMenuCreationTest : public testing::Test
{

};

TEST_F(ButtonMenuCreationTest, buttonMenuPositionsTextWithinBoundsOfContainer)
{
    const sf::VideoMode resolution{1920, 1080};
    const sf::Vector2f size{30.f, 70.f};
    const sf::Vector2f position{480.f, 480.f};
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();

    auto sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));
    const auto result = sut->getTextContent().getPosition();
    EXPECT_GT(result.x, position.x);
    EXPECT_LT(result.x, position.x + size.x);
    EXPECT_GT(result.y, position.y);
    EXPECT_LT(result.y, position.y + size.y);
}

TEST_F(ButtonMenuCreationTest, buttonMenuWillAddButtonWithPositionWithinBoundsOfContainer)
{
    const sf::VideoMode resolution{1920, 1080};
    const sf::Vector2f size{30.f, 70.f};
    const sf::Vector2f position{480.f, 480.f};
    auto buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
    auto dummyCallback = [](States::GameState&){};
    EXPECT_CALL(*buttonBuilder, withTextContent(StrEq("test"))).WillOnce(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, withFont(A<std::shared_ptr<sf::Font>>())).WillOnce(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, atPosition(FloatNear(480.f, 1), FloatNear(503.f, 1))).WillOnce(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, withSize(FloatNear(15.f, 1), FloatNear(11.f, 1))).WillOnce(ReturnRef(*buttonBuilder));
    EXPECT_CALL(*buttonBuilder, build())
            .WillOnce(Return(ByMove(std::make_unique<NiceMock<ButtonMock>>())));
    auto sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));
    sut->addSection("test", dummyCallback);
    const auto result = sut->getTextContent().getPosition();
}

struct ButtonMenuBehaviourTest : public testing::Test
{
    ButtonMenuBehaviourTest()
    {
        buttonBuilder = std::make_unique<NiceMock<ButtonBuilderMock>>();
        ON_CALL(*buttonBuilder, withTextContent(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withFont(_)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, atPosition(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
        ON_CALL(*buttonBuilder, withSize(_, _)).WillByDefault(ReturnRef(*buttonBuilder));
    }
    const sf::VideoMode resolution{1920, 1080};
    const sf::Vector2f size{30.f, 70.f};
    const sf::Vector2f position{480.f, 480.f};
    std::unique_ptr<NiceMock<ButtonBuilderMock>> buttonBuilder;
    std::unique_ptr<ButtonMenu> sut;
    NiceMock<Core::WindowMock> window;
};

TEST_F(ButtonMenuBehaviourTest, buttonMenuWillGetLastSectionParamsToCreateNewSectionWhenAddingOverOneSection)
{
    const sf::Vector2f lastAddedButtonPosition{3.f, 3.f};
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, getPosition())
        .WillOnce(Return(lastAddedButtonPosition))
        .WillOnce(Return(lastAddedButtonPosition));
    auto testButton2 = std::make_unique<NiceMock<ButtonMock>>();

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))))
        .WillOnce(Return(ByMove(std::move(testButton2))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));

    sut->addSection("test1", [](States::GameState&){});
    sut->addSection("test2", [](States::GameState&){});
}

TEST_F(ButtonMenuBehaviourTest, buttonMenuWillGetLastSectionAndNewestSectionParamsToCreateNewSectionWhenAddingOverTwoSections)
{
    const sf::Vector2f firstAddedButtonPosition{3.f, 3.f};
    const sf::Vector2f lastAddedButtonPosition{3.f, 13.f};
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, getPosition())
        .WillOnce(Return(lastAddedButtonPosition))
        .WillOnce(Return(lastAddedButtonPosition))
        .WillOnce(Return(lastAddedButtonPosition));
    auto testButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton2, getPosition())
        .WillOnce(Return(lastAddedButtonPosition));
    auto testButton3 = std::make_unique<NiceMock<ButtonMock>>();

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))))
        .WillOnce(Return(ByMove(std::move(testButton2))))
        .WillOnce(Return(ByMove(std::move(testButton3))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));

    sut->addSection("test1", [](States::GameState&){});
    sut->addSection("test2", [](States::GameState&){});
    sut->addSection("test3", [](States::GameState&){});
}

TEST_F(ButtonMenuBehaviourTest, buttonMenuWillUpdateItsButtonsWithGivenPosition)
{
    const sf::Vector2i mousePosition{3, 3};
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, update(Eq(mousePosition)));
    auto testButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton2, update(Eq(mousePosition)));
    auto testButton3 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton3, update(Eq(mousePosition)));
    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))))
        .WillOnce(Return(ByMove(std::move(testButton2))))
        .WillOnce(Return(ByMove(std::move(testButton3))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));


    sut->addSection("test", [](States::GameState&){});
    sut->addSection("test1", [](States::GameState&){});
    sut->addSection("test2", [](States::GameState&){});
    sut->update(mousePosition);
}

TEST_F(ButtonMenuBehaviourTest, buttonMenuWillRenderButtonsAndContainerAndTextAndBackgroundIntoWindow)
{
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, getBackground())
        .WillOnce(Return(sf::RectangleShape{}));
    EXPECT_CALL(*testButton1, getTextContent())
        .WillOnce(Return(sf::Text{}));

    auto testButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton2, getBackground())
        .WillOnce(Return(sf::RectangleShape{}));
    EXPECT_CALL(*testButton2, getTextContent())
        .WillOnce(Return(sf::Text{}));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))))
        .WillOnce(Return(ByMove(std::move(testButton2))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));
    sut->addSection("test", [](States::GameState&){});
    sut->addSection("test1", [](States::GameState&){});

    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(7);
    sut->drawTo(window);
}


TEST_F(ButtonMenuBehaviourTest, buttonMenuWillReturnAStateActionOnceWhenSectionIsPressedOnce)
{
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, update(Eq(sf::Vector2i{3, 3}))).Times(2);
    EXPECT_CALL(*testButton1, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));

    std::function<void(States::GameState&)> dummyCallback = [](States::GameState&){};
    sut->addSection("FirstSection", dummyCallback);
    sut->update(sf::Vector2i{3, 3});
    auto result = sut->getActiveAction();
    ASSERT_NE(result, std::nullopt);
    EXPECT_TRUE(std::holds_alternative<Events::GameAction>(result.value()));
    sut->update(sf::Vector2i{3, 3});
    ASSERT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(ButtonMenuBehaviourTest, buttonMenuWillReturnNulloptWhenNoSectionIsPressed)
{
    auto testButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*testButton1, update(Eq(sf::Vector2i{3, 3})));
    EXPECT_CALL(*testButton1, isPressed())
        .WillOnce(Return(false));

    EXPECT_CALL(*buttonBuilder, build())
        .WillOnce(Return(ByMove(std::move(testButton1))));
    sut = std::make_unique<ButtonMenu>(
        "test",
        std::make_shared<sf::Font>(),
        resolution,
        size,
        position,
        std::move(buttonBuilder));

    std::function<void(States::GameState&)> dummyCallback = [](States::GameState&){};
    sut->addSection("FirstSection", dummyCallback);
    sut->update(sf::Vector2i{3, 3});
    ASSERT_EQ(sut->getActiveAction(), std::nullopt);
}


}