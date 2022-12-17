#include <State.h>

namespace States
{

State::State(
    Core::Config& config,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
    : assetsManager(std::move(assetsManager)),
      config{config}
{

}

}