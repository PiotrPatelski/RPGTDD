#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <MainMenuState.hpp>

namespace Events
{

std::unique_ptr<States::IState> ToMainMenuState::operator()(std::shared_ptr<Core::IConfigManager> configManager)
{
    return std::make_unique<States::MainMenuState>(
    configManager,
    std::make_unique<FileMgmt::MainMenuAssetsManager>(),
    std::make_unique<Gui::MainMenuGuiManager>(configManager->getGraphics().resolution),
    std::make_unique<MainMenuInputHandler>(configManager));
}

std::unique_ptr<States::IState> ToGameState::operator()(std::shared_ptr<Core::IConfigManager> configManager)
{
    return std::make_unique<States::GameState>(
    configManager,
    std::make_unique<FileMgmt::GameAssetsManager>(),
    std::make_unique<Gui::GameGuiManager>(configManager->getGraphics().resolution),
    std::make_unique<GameInputHandler>(configManager));
}

std::unique_ptr<States::IState> ToSettingsState::operator()(std::shared_ptr<Core::IConfigManager> configManager)
{
    return std::make_unique<States::SettingsState>(
    configManager,
    std::make_unique<FileMgmt::SettingsAssetsManager>(),
    std::make_unique<Gui::SettingsGuiManager>(configManager->getGraphics().resolution),
    std::make_unique<SettingsInputHandler>(configManager));
}

std::unique_ptr<States::IState> ToEditorState::operator()(std::shared_ptr<Core::IConfigManager> configManager)
{
    return std::make_unique<States::EditorState>(
    configManager,
    std::make_unique<FileMgmt::EditorAssetsManager>(),
    std::make_unique<Gui::EditorGuiManager>(configManager->getGraphics().resolution),
    std::make_unique<EditorInputHandler>(configManager));
}

std::unique_ptr<States::IState> ToExitState::operator()(std::shared_ptr<Core::IConfigManager> configManager)
{
    return nullptr;
}

}