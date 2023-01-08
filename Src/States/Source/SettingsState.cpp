#include <SettingsState.hpp>

namespace States
{

SettingsState::SettingsState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::SettingsAssetsManager> assetsManager,
    std::unique_ptr<Gui::SettingsGuiManager> guiManager,
    std::unique_ptr<Events::SettingsInputHandler> inputHandler)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager),
        std::move(inputHandler))
{}

}