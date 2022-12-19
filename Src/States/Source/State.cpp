#include <State.h>

namespace States
{

State::State(
    Core::Config& config,
    std::unique_ptr<Core::IAssetsManager> assetsManager,
    std::unique_ptr<Gui::IGuiManager> guiManager)
    : config{config},
      assetsManager(std::move(assetsManager)),
      guiManager(std::move(guiManager))
{

}

}