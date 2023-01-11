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
    ASSERT_EQ(buttons[0].object->getTextContent().getString(), "New Game");
    ASSERT_EQ(buttons[1].object->getTextContent().getString(), "Settings");
    ASSERT_EQ(buttons[2].object->getTextContent().getString(), "Editor");
    ASSERT_EQ(buttons[3].object->getTextContent().getString(), "Exit");
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithTextColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0].object->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[1].object->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[2].object->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[3].object->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithBackgroundColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0].object->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[1].object->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[2].object->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[3].object->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithOutlineColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0].object->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[1].object->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[2].object->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[3].object->getBackground().getOutlineColor(), sf::Color::Transparent);
}

struct SettingsGuiManagerTest : public testing::Test
{
    std::unique_ptr<IGuiManager> sut = std::make_unique<SettingsGuiManager>(sf::VideoMode(1920, 1080));
};

TEST_F(SettingsGuiManagerTest, settingsGuiManagerWillCreateMapOfValidStateChangingButtons)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0].object->getTextContent().getString(), "Back");
}

}