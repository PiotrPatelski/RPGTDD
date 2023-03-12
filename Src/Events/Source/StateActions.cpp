#include <StateActions.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <MainMenuState.hpp>
#include <DropDownListBuilder.hpp>
#include <GameMapManager.hpp>

namespace Events
{
void toMainMenu(States::IState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::MainMenuState>(
        config,
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::MainMenuGuiManager>(
            config->getGraphics().resolution,
            std::make_unique<Gui::MenuButtonBuilder>()
        )));
    state.finishState();
}

void ToMainMenuState::operator()(States::MenuState& state)
{
    toMainMenu(state);
}

void ExitMapState::operator()(States::MapState& state)
{
    toMainMenu(state);
}

void ToGameState::operator()(States::MenuState& state)
{
    state.setNextState(std::make_unique<States::GameState>(
        state.getConfig(),
        std::make_unique<FileMgmt::GameAssetsManager>(),
        std::make_unique<Gui::GameGuiManager>(
            std::make_unique<Gui::MenuButtonBuilder>()
        )));
    state.finishState();
}

void ToSettingsState::operator()(States::MenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::SettingsState>(
        config,
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            config->getGraphics().resolution,
            std::make_unique<Gui::MenuButtonBuilder>(),
            std::make_unique<Gui::DropDownListBuilder>()),
        std::make_unique<Events::MenuInputListener>(config->getKeyboard())));
    state.finishState();
}

void ToEditorState::operator()(States::MenuState& state)
{
    auto config = state.getConfig();
    state.setNextState(std::make_unique<States::EditorState>(
        config,
        std::make_unique<FileMgmt::EditorAssetsManager>(),
        std::make_unique<Gui::EditorGuiManager>(
            config->getGraphics().resolution,
            std::make_unique<Gui::MenuButtonBuilder>(),
            std::make_unique<Gui::ButtonMenuBuilder>()),
        std::make_unique<Tiles::GameMapManager>(),
        std::make_unique<Events::EditorInputListener>(config->getKeyboard())));
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
        std::make_unique<FileMgmt::MainMenuAssetsManager>(),
        std::make_unique<Gui::SettingsGuiManager>(
            config->getGraphics().resolution,
            std::make_unique<Gui::MenuButtonBuilder>(),
            std::make_unique<Gui::DropDownListBuilder>()),
        std::make_unique<Events::MenuInputListener>(config->getKeyboard())));
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

void Pause::operator()(States::MapState& state)
{
    state.togglePause();
}

}