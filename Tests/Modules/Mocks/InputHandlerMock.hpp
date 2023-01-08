#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <InputHandler.hpp>


namespace Events
{

class MainMenuInputHandlerMock : public MainMenuInputHandler
{
public:
    MainMenuInputHandlerMock()
    : MainMenuInputHandler(std::make_shared<Core::ConfigManager>()){}
    MOCK_METHOD(std::unique_ptr<States::IState>, getNextStateOnActiveButton, (const Gui::IButton&), (override));
    MOCK_METHOD(const bool, isStateReadyToChange, (), (const, override));
};

class GameInputHandlerMock : public GameInputHandler
{
public:
    GameInputHandlerMock()
    : GameInputHandler(std::make_shared<Core::ConfigManager>()){}
    MOCK_METHOD(std::unique_ptr<States::IState>, getNextStateOnActiveButton, (const Gui::IButton&), (override));
    MOCK_METHOD(const bool, isStateReadyToChange, (), (const, override));
};

class SettingsInputHandlerMock : public SettingsInputHandler
{
public:
    SettingsInputHandlerMock()
    : SettingsInputHandler(std::make_shared<Core::ConfigManager>()){}
    MOCK_METHOD(std::unique_ptr<States::IState>, getNextStateOnActiveButton, (const Gui::IButton&), (override));
    MOCK_METHOD(const bool, isStateReadyToChange, (), (const, override));
};

class EditorInputHandlerMock : public EditorInputHandler
{
public:
    EditorInputHandlerMock()
    : EditorInputHandler(std::make_shared<Core::ConfigManager>()){}
    MOCK_METHOD(std::unique_ptr<States::IState>, getNextStateOnActiveButton, (const Gui::IButton&), (override));
    MOCK_METHOD(const bool, isStateReadyToChange, (), (const, override));
};

}