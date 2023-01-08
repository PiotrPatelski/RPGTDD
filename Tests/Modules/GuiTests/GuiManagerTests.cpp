#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

struct MainMenuGuiManagerTest : public testing::Test
{
    std::unique_ptr<IGuiManager> sut = std::make_unique<MainMenuGuiManager>(sf::VideoMode(1920, 1080));
};

// TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfValidMainMenuButtons)
// {
//     auto buttons = sut->createButtons(sf::Font{});
//     ASSERT_EQ(buttons[0]->getId(), "GAME_STATE");
//     ASSERT_EQ(buttons[1]->getId(), "SETTINGS_STATE");
//     ASSERT_EQ(buttons[2]->getId(), "EDITOR_STATE");
//     ASSERT_EQ(buttons[3]->getId(), "EXIT_STATE");
// }

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithTextColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0]->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[1]->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[2]->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
    ASSERT_EQ(buttons[3]->getTextContent().getFillColor(), sf::Color(70, 70, 70, 200));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithBackgroundColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0]->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[1]->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[2]->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
    ASSERT_EQ(buttons[3]->getBackground().getFillColor(), sf::Color(70, 70, 70, 50));
}

TEST_F(MainMenuGuiManagerTest, guiManagerWillCreateMapOfMainMenuButtonsWithOutlineColorSet)
{
    auto buttons = sut->createButtons(sf::Font{});
    ASSERT_EQ(buttons[0]->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[1]->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[2]->getBackground().getOutlineColor(), sf::Color::Transparent);
    ASSERT_EQ(buttons[3]->getBackground().getOutlineColor(), sf::Color::Transparent);
}

}