#include <State.hpp>

namespace States
{

State::State(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::IAssetsManager> assetsManager)
    : config(config),
      assetsManager(std::move(assetsManager))
{}

}