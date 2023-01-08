#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>

namespace States
{

class EditorState : public State
{
public:
    EditorState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::EditorAssetsManager>,
        std::unique_ptr<Gui::EditorGuiManager>,
        std::unique_ptr<Events::EditorInputHandler>);
    virtual ~EditorState() = default;

    virtual void update(const sf::Vector2i&, const float) override {}
    virtual void drawOutput(Core::IWindow&) override {}
private:

};

}