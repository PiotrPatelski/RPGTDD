#include <StateActions.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <MainMenuState.hpp>
#include <DropDownListBuilder.hpp>

namespace Events
{

void ToMainMenuState::operator()(States::MenuState& state)
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

void ToGameState::operator()(States::MenuState& state)
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

void ToSettingsState::operator()(States::MenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::SettingsState>(
        config,
        std::make_unique<FileMgmt::SettingsAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution),
            std::make_unique<Gui::DropDownListBuilder>()),
        std::make_unique<Events::InputListener>(config->getKeyboard().mainMenuKeys)));
    state.finishState();
}

void ToEditorState::operator()(States::MenuState& state)
{
    auto config = state.getConfig();
    auto resolution = config->getGraphics().resolution;
    state.setNextState(std::make_unique<States::EditorState>(
        config,
        std::make_unique<FileMgmt::EditorAssetsManager>(),
        std::make_unique<Gui::EditorGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(resolution),
            resolution
        )));
    state.finishState();
}

void ToExitState::operator()(States::MenuState& state)
{
    state.setNextState(nullptr);
    state.finishState();
}

void ApplySettings::operator()(States::MenuState& state)
{
    auto config = state.getConfig();
    config->applyDiff();
    state.setNextState(std::make_unique<States::SettingsState>(
        config,
        std::make_unique<FileMgmt::SettingsAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            std::make_unique<Gui::ButtonBuilder>(config->getGraphics().resolution),
            std::make_unique<Gui::DropDownListBuilder>()),
        std::make_unique<Events::InputListener>(config->getKeyboard().mainMenuKeys)));
    state.finishState();
}

SetResolutionTo::SetResolutionTo(const sf::VideoMode& mode)
: value(mode)
{}

void SetResolutionTo::operator()(States::MenuState& state)
{
    auto targetResolution = value;
    state.getConfig()->queueGraphicsRequest(
        [targetResolution](FileMgmt::GraphicsConfig& diff)
        {
            diff.resolution = targetResolution;
        });
}

}