#include <State.h>

namespace States
{

State::State(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
    : assetsManager(std::move(assetsManager)),
      gfxConfig{gfxConfig},
      kbrdConfig{kbrdConfig}
{

}

}