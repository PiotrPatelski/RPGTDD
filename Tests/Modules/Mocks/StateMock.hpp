#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <MainMenuState.hpp>
#include <SettingsState.hpp>

namespace States
{

using ::testing::Test;
using testing::Return;

class StateMock : public IState
{
public:
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (Core::IWindow&), (override));
    MOCK_METHOD(void, update, (const Core::IWindow&, const float), (override));
};

class MainMenuStateMock : public MainMenuState
{
public:
    MainMenuStateMock(std::shared_ptr<Core::IConfigManager> configManager)
    : MainMenuState(
        configManager,
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(configManager->getGraphics().resolution)
        ))
    {}
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (Core::IWindow&), (override));
    MOCK_METHOD(void, update, (const Core::IWindow&, const float), (override));
};

class SettingsStateMock : public SettingsState
{
public:
    SettingsStateMock(std::shared_ptr<Core::IConfigManager> configManager)
    : SettingsState(
        configManager,
        std::make_unique<FileMgmt::SettingsAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(configManager->getGraphics().resolution)
        ))
    {}
    MOCK_METHOD(void, finishState, (), ());
    MOCK_METHOD(void, setNextState, (std::unique_ptr<IState>), (override));
    MOCK_METHOD(std::unique_ptr<IState>, getNextState, (), (override));
    MOCK_METHOD(const bool, isReadyToChange, (), (const override));
    MOCK_METHOD(std::shared_ptr<Core::IConfigManager>, getConfig, (), ());
    MOCK_METHOD(void, drawOutput, (Core::IWindow&), (override));
    MOCK_METHOD(void, update, (const Core::IWindow&, const float), (override));
};

}