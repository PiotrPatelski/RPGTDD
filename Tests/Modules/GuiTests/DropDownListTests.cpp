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
    NiceMock<::Types::WindowMock> window;
    sf::VideoMode resolution{1920, 1080};
    ::Types::Background dummyBackground{
        VectorMath::ScreenPercentagePoint{resolution, {0,0}},
        VectorMath::ScreenPercentagePoint{resolution, {0,0}}};
};

TEST_F(DropDownListTest, dropDownListWillUpdateItsInitiatingButtonAndCheckIfItsPressed)
{
    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, update(Eq(sf::Vector2i{3, 3})));
    EXPECT_CALL(*initiatingButton, isPressed()).WillOnce(Return(false));
    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::vector<ActionButton>{});
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
        std::move(initiatingButton),
        std::vector<ActionButton>{});

    EXPECT_FALSE(sut->isActive());
    sut->update(sf::Vector2i{3, 3});
    EXPECT_TRUE(sut->isActive());
    sut->update(sf::Vector2i{3, 3});
    EXPECT_FALSE(sut->isActive());
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
    std::vector<ActionButton> sections;
    sections.push_back(ActionButton{std::move(sectionButton), std::monostate{}});

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::move(sections));

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
    std::vector<ActionButton> sections;
    sections.push_back(ActionButton{std::move(sectionButton), std::monostate{}});

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::move(sections));

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
        std::move(initiatingButton),
        std::vector<ActionButton>{});

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
    std::vector<ActionButton> sections;
    sections.push_back(ActionButton{std::move(sectionButton), [](States::MenuState&){}});

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::move(sections));

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

    std::vector<ActionButton> sections;
    sections.push_back(ActionButton{std::move(sectionButton1), [](States::MenuState&){}});
    sections.push_back(ActionButton{std::move(sectionButton2), [](States::MenuState&){}});
    sections.push_back(ActionButton{std::move(sectionButton3), [](States::MenuState&){}});

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::move(sections));

    sut->update(sf::Vector2i{3, 3});
    ASSERT_EQ(sut->getActiveAction(), std::nullopt);
}

TEST_F(DropDownListTest, dropDownListWillDrawBothInitiatingButtonAndSectionsWhenActive)
{
    auto sectionButton1 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton1, getBackground())
        .WillOnce(Return(dummyBackground));
    EXPECT_CALL(*sectionButton1, getTextContent())
        .WillOnce(Return(sf::Text{}));

    auto sectionButton2 = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*sectionButton2, getBackground())
        .WillOnce(Return(dummyBackground));
    EXPECT_CALL(*sectionButton2, getTextContent())
        .WillOnce(Return(sf::Text{}));

    auto initiatingButton = std::make_unique<NiceMock<ButtonMock>>();
    EXPECT_CALL(*initiatingButton, isPressed())
        .WillOnce(Return(true));
    EXPECT_CALL(*initiatingButton, getBackground())
        .WillOnce(Return(dummyBackground));
    EXPECT_CALL(*initiatingButton, getTextContent())
        .WillOnce(Return(sf::Text{}));

    std::vector<ActionButton> sections;
    sections.push_back(ActionButton{std::move(sectionButton1), [](States::MenuState&){}});
    sections.push_back(ActionButton{std::move(sectionButton2), [](States::MenuState&){}});

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::move(sections));

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
        .WillByDefault(Return(dummyBackground));
    ON_CALL(*initiatingButton, getTextContent())
        .WillByDefault(Return(sf::Text{}));

    auto sut = std::make_unique<DropDownList>(
        sf::Text{},
        std::move(initiatingButton),
        std::vector<ActionButton>{});

    //draw list text and button background and button text
    EXPECT_CALL(window, draw(A<const sf::Drawable&>())).Times(3);
    sut->drawTo(window);
}

}