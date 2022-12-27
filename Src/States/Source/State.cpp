#include <State.h>

namespace States
{

State::State(
    std::shared_ptr<Core::ConfigManager> config,
    std::unique_ptr<FileMgmt::IAssetsManager> assetsManager,
    std::unique_ptr<Gui::IGuiManager> guiManager)
    : config(config),
      assetsManager(std::move(assetsManager)),
      guiManager(std::move(guiManager))
{

}

}