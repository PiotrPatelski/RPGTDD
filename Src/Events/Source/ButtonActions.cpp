#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <MainMenuState.hpp>

namespace Events
{

void ToMainMenuState::operator()(States::SettingsState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::MainMenuState>(
        config,
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution)
        )));
    state.finishState();
}

void ToGameState::operator()(States::MainMenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::GameState>(
        config,
        std::make_unique<FileMgmt::GameAssetsManager>(),
        std::make_unique<Gui::GameGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution)
        )));
    state.finishState();
}

void ToSettingsState::operator()(States::MainMenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::SettingsState>(
        config,
        std::make_unique<FileMgmt::SettingsAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution)
        )));
    state.finishState();
}

void ToEditorState::operator()(States::MainMenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::EditorState>(
        config,
        std::make_unique<FileMgmt::EditorAssetsManager>(),
        std::make_unique<Gui::EditorGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution)
        )));
    state.finishState();
}

void ToExitState::operator()(States::MainMenuState& state)
{
    state.setNextState(nullptr);
    state.finishState();
}

void ApplySettings::operator()(States::SettingsState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::SettingsState>(
        config,
        std::make_unique<FileMgmt::SettingsAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution)
        )));
    state.finishState();
}

}