#pragma once

#include <SFML/Graphics.hpp>
#include <MapState.hpp>
#include <ConfigManager.hpp>
#include <EditorAssetsManager.hpp>
#include <EditorGuiManager.hpp>
#include <TileMap.hpp>
#include <UserInterface.hpp>

namespace Tiles
{
class TileMapManager;
}

namespace Events
{
class InputListener;
}

namespace States
{

class EditorState : public MapState
{
public:
    EditorState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>,
        std::unique_ptr<Gui::GuiManager>,
        std::unique_ptr<Tiles::TileMapManager>,
        std::unique_ptr<Events::InputListener>);
    virtual ~EditorState() = default;

    virtual void update(const Types::IWindow&, const float) override;
    virtual void drawOutput(Types::IWindow&) override;
    virtual void togglePause() override;
private:
    std::unique_ptr<Gui::UserInterface> gui;
    std::unique_ptr<Tiles::TileMap> tileMap;
    std::unique_ptr<Events::InputListener> inputListener;
};

}