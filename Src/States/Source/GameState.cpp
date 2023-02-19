#include <GameState.hpp>

namespace States
{

GameState::GameState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager)
    : MapState(
        config,
        std::move(assetsManager))
{}

}