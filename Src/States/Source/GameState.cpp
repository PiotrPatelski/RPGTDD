#include <GameState.hpp>

namespace States
{

GameState::GameState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::GameAssetsManager> assetsManager,
    std::unique_ptr<Gui::GameGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager))
{}

}