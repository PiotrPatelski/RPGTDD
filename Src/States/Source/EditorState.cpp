#include <EditorState.hpp>

namespace States
{

EditorState::EditorState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::EditorAssetsManager> assetsManager,
    std::unique_ptr<Gui::IGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager))
{}

}