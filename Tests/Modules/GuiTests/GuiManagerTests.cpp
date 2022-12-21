#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

struct MainMenuGuiManagerTest : public testing::Test
{
    std::unique_ptr<IGuiManager> sut = std::make_unique<MainMenuGuiManager>(sf::VideoMode(1920, 1080));
};

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfValidMainMenuButtons)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_NO_THROW(buttons.at("GAME_STATE"));
    ASSERT_NO_THROW(buttons.at("SETTINGS_STATE"));
    ASSERT_NO_THROW(buttons.at("EDITOR_STATE"));
    ASSERT_NO_THROW(buttons.at("EXIT_STATE"));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithTextColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons.at("GAME_STATE")->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons.at("SETTINGS_STATE")->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons.at("EDITOR_STATE")->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons.at("EXIT_STATE")->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithBackgroundColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons.at("GAME_STATE")->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons.at("SETTINGS_STATE")->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons.at("EDITOR_STATE")->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons.at("EXIT_STATE")->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithOutlineColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons.at("GAME_STATE")->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons.at("SETTINGS_STATE")->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons.at("EDITOR_STATE")->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons.at("EXIT_STATE")->getBackground().getOutlineColor(), sf::Color::Transparent);
}

}