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
    : MainMenuGuiManager(sf::VideoMode()){}
    MOCK_METHOD(std::vector<StateChangingButton>, createButtons, (const sf::Font&), (override));
};

class GameGuiManagerMock : public GameGuiManager
{
public:
    GameGuiManagerMock()
    : GameGuiManager(sf::VideoMode()){}
    MOCK_METHOD(std::vector<StateChangingButton>, createButtons, (const sf::Font&), (override));
};

class SettingsGuiManagerMock : public SettingsGuiManager
{
public:
    SettingsGuiManagerMock()
    : SettingsGuiManager(sf::VideoMode()){}
    MOCK_METHOD(std::vector<StateChangingButton>, createButtons, (const sf::Font&), (override));
};

class EditorGuiManagerMock : public EditorGuiManager
{
public:
    EditorGuiManagerMock()
    : EditorGuiManager(sf::VideoMode()){}
    MOCK_METHOD(std::vector<StateChangingButton>, createButtons, (const sf::Font&), (override));
};

}