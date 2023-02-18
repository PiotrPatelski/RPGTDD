#include <State.hpp>

namespace States
{

State::State(
    std::shared_ptr<Core::IConfigManager> configManager,
    std::unique_ptr<FileMgmt::AssetsManager> assetsManager)
    : configManager(configManager),
      assetsManager(std::move(assetsManager))
{}

}