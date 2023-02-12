#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <DropDownList.hpp>
#include <ButtonMock.hpp>
#include <WindowMock.hpp>

namespace Gui
{

using namespace ::testing;

struct DropDownListTest : public testing::Test
{
    NiceMock<Core::WindowMock> window;
};

TEST_F(DropDownListTest, dropDownListWillGetInitiatingButtonPositionToSetTextPositionWithHardcodedOffsetUponCreation)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    const sf::Vector2f buttonPosition{50, 50};
    EXPECT_CALL(*initiatingButton, getPosition()).WillOnce(Return(buttonPosition));
    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));
    const auto result = sut->getTextContent().getPosition();
    EXPECT_EQ(result.x, buttonPosition.x + 13);
    EXPECT_EQ(result.y, buttonPosition.y - 40);
}

TEST_F(DropDownListTest, dropDownListWillGetInitiatingButtonPositionToSetTextPositionWithZeroYWhenCalculatedPosIsLessThanZero)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    const sf::Vector2f buttonPosition{3, 3};
    EXPECT_CALL(*initiatingButton, getPosition()).WillOnce(Return(buttonPosition));
    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));
    const auto result = sut->getTextContent().getPosition();
    EXPECT_EQ(result.x, buttonPosition.x + 13);
    EXPECT_EQ(result.y, 0);
}

TEST_F(DropDownListTest, dropDownListWillUpdateItsInitiatingButtonAndCheckIfItsPressed)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3})));
    EXPECT_CALL(*initiatingButton, isPressed()).WillOnce(Return(false));
    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));
    sut->update(sf::Vector2i{3, 3});
}

TEST_F(DropDownListTest, dropDownListWillActivateOrHideDependingOnItsPreviousStatusWhenInitiatingButtonIsPressed)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3}))).Times(2);
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(true));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    EXPECT_FALSE(sut->isActive());
    sut->update(sf::Vector2i{3, 3});
    EXPECT_TRUE(sut->isActive());
    sut->update(sf::Vector2i{3, 3});
    EXPECT_FALSE(sut->isActive());
}

TEST_F(DropDownListTest, addSectionWillCloneInitiatingButton)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    auto sectionButton1 = std::make_unique<NiceMock<ButtonMock>>();
    auto sectionButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, getSize()).WillOnce(Return(sf::Vector2f{10.f, 10.f}));
    EXPECT_CALL(*initiatingButton, getPosition())
        .WillOnce(Return(sf::Vector2f{3.f, 3.f}))
        .WillOnce(Return(sf::Vector2f{3.f, 3.f}));
    EXPECT_CALL(*sectionButton1, getSize()).WillOnce(Return(sf::Vector2f{10.f, 10.f}));
    EXPECT_CALL(*sectionButton1, getPosition()).WillOnce(Return(sf::Vector2f{3.f, 13.f}));
    EXPECT_CALL(*initiatingButton, clone(StrEq("FirstSection"), Eq(sf::Vector2f{3.f, 13.f})))
        .WillOnce(Return(ByMove(std::move(sectionButton1))));
    EXPECT_CALL(*initiatingButton, clone(StrEq("SecondSection"), Eq(sf::Vector2f{3.f, 23.f})))
        .WillOnce(Return(ByMove(std::move(sectionButton2))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", std::monostate{});
    sut->addSection("SecondSection", std::monostate{});
}

TEST_F(DropDownListTest, dropDownListWillUpdateSectionsOnceActivated)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3}))).Times(3);
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(false));
    auto sectionButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton, update(Eq(sf::Vector2i{3, 3}))).Times(3);
    EXPECT_CALL(*initiatingButton, clone(_, _))
        .WillOnce(Return(ByMove(std::move(sectionButton))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", std::monostate{});
    sut->update(sf::Vector2i{3, 3});
    sut->update(sf::Vector2i{3, 3});
    sut->update(sf::Vector2i{3, 3});
}

TEST_F(DropDownListTest, dropDownListWillStopUpdatingSectionsOnceInitiatingButtonIsPressedAgain)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3}))).Times(3);
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    auto sectionButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton, update(Eq(sf::Vector2i{3, 3}))).Times(1);
    EXPECT_CALL(*initiatingButton, clone(_, _))
        .WillOnce(Return(ByMove(std::move(sectionButton))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", std::monostate{});
    sut->update(sf::Vector2i{3, 3});
    sut->update(sf::Vector2i{3, 3});
    sut->update(sf::Vector2i{3, 3});
}

TEST_F(DropDownListTest, dropDownListWillReturnNulloptWhenNoSectionsAreToBePressed)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3})));
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->update(sf::Vector2i{3, 3});
    EXPECT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(DropDownListTest, dropDownListWillReturnAMenuActionOnceWhenSectionIsPressedOnce)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3}))).Times(2);
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    auto sectionButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton, update(Eq(sf::Vector2i{3, 3}))).Times(2);
    EXPECT_CALL(*sectionButton, isPressed())
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(*initiatingButton, clone(_, _))
        .WillOnce(Return(ByMove(std::move(sectionButton))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", [](States::MenuState&){});
    sut->update(sf::Vector2i{3, 3});
    ASSERT_NE(sut->getActiveAction(), std::nullopt);
    EXPECT_TRUE(std::holds_alternative<Events::MenuAction>(sut->getActiveAction().value()));
    sut->update(sf::Vector2i{3, 3});
    ASSERT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(DropDownListTest, dropDownListWillReturnNulloptWhenNoneOfExistingSectionsArePressed)
{
    auto sectionButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton1, update(_));
    EXPECT_CALL(*sectionButton1, isPressed())
        .WillOnce(Return(false));

    auto sectionButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton2, update(_));
    EXPECT_CALL(*sectionButton2, isPressed())
        .WillOnce(Return(false));

    auto sectionButton3 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton3, update(_));
    EXPECT_CALL(*sectionButton3, isPressed())
        .WillOnce(Return(false));

    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(_));
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true));

    EXPECT_CALL(*initiatingButton, clone(_, _))
        .WillOnce(Return(ByMove(std::move(sectionButton1))))
        .WillOnce(Return(ByMove(std::move(sectionButton2))))
        .WillOnce(Return(ByMove(std::move(sectionButton3))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", [](States::MenuState&){});
    sut->addSection("SecondSection", [](States::MenuState&){});
    sut->addSection("ThirdSection", [](States::MenuState&){});
    sut->update(sf::Vector2i{3, 3});
    ASSERT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(DropDownListTest, dropDownListWillDrawBothInitiatingButtonAndSectionsWhenActive)
{
    auto sectionButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton1, getBackground())
        .WillOnce(Return(sf::RectangleShape{}));
    EXPECT_CALL(*sectionButton1, getTextContent())
        .WillOnce(Return(sf::Text{}));

    auto sectionButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton2, getBackground())
        .WillOnce(Return(sf::RectangleShape{}));
    EXPECT_CALL(*sectionButton2, getTextContent())
        .WillOnce(Return(sf::Text{}));

    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true));
    EXPECT_CALL(*initiatingButton, getBackground())
        .WillOnce(Return(sf::RectangleShape{}));
    EXPECT_CALL(*initiatingButton, getTextContent())
        .WillOnce(Return(sf::Text{}));

    EXPECT_CALL(*initiatingButton, clone(_, _))
        .WillOnce(Return(ByMove(std::move(sectionButton1))))
        .WillOnce(Return(ByMove(std::move(sectionButton2))));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    sut->addSection("FirstSection", std::monostate{});
    sut->addSection("SecondSection", std::monostate{});

    sut->update(sf::Vector2i{3, 3});
    //draw list text and Twice per section, including initiatingButton
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(7);
    sut->drawTo(window);
}

TEST_F(DropDownListTest, dropDownListWillDrawItsTextContent)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    ON_CALL(*initiatingButton, isPressed())
        .WillByDefault(Return(false));
    ON_CALL(*initiatingButton, getBackground())
        .WillByDefault(Return(sf::RectangleShape{}));
    ON_CALL(*initiatingButton, getTextContent())
        .WillByDefault(Return(sf::Text{}));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton));

    //draw list text and button background and button text
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(3);
    sut->drawTo(window);
}

}