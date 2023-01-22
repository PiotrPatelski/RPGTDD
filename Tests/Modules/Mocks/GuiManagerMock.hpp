#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GuiManager.hpp>

namespace Gui
{

using ::testing::Test;
using testing::Return;

class MainMenuGuiManagerMock : public MainMenuGuiManager
{
public:
    MainMenuGuiManagerMock()
    : MainMenuGuiManager(std::make_unique<Gui::ButtonBuilder>(sf::VideoMode()))
    {}
    MOCK_METHOD(std::unique_ptr<Gui::IUserInterface>, createGui, (const std::shared_ptr<sf::Font>), (override));
};

class GameGuiManagerMock : public GameGuiManager
{
public:
    GameGuiManagerMock()
    : GameGuiManager(std::make_unique<Gui::ButtonBuilder>(sf::VideoMode()))
    {}
    MOCK_METHOD(std::unique_ptr<Gui::IUserInterface>, createGui, (const std::shared_ptr<sf::Font>), (override));
};

class SettingsGuiManagerMock : public SettingsGuiManager
{
public:
    SettingsGuiManagerMock()
    : SettingsGuiManager(std::make_unique<Gui::ButtonBuilder>(sf::VideoMode()))
    {}
    MOCK_METHOD(std::unique_ptr<Gui::IUserInterface>, createGui, (const std::shared_ptr<sf::Font>), (override));
};

class EditorGuiManagerMock : public EditorGuiManager
{
public:
    EditorGuiManagerMock()
    : EditorGuiManager(std::make_unique<Gui::ButtonBuilder>(sf::VideoMode()))
    {}
    MOCK_METHOD(std::unique_ptr<Gui::IUserInterface>, createGui, (const std::shared_ptr<sf::Font>), (override));
};

}