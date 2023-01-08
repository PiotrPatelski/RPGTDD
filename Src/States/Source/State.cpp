#include <State.hpp>

namespace States
{

State::State(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::IAssetsManager> assetsManager,
    std::unique_ptr<Gui::IGuiManager> guiManager,
    std::unique_ptr<Events::IInputHandler> inputHandler)
    : config(config),
      assetsManager(std::move(assetsManager)),
      guiManager(std::move(guiManager)),
      inputHandler(std::move(inputHandler))
{}

}