#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <GuiManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class EditorState : public State
{
public:
    EditorState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::EditorAssetsManager>,
        std::unique_ptr<Gui::EditorGuiManager>);
    virtual ~EditorState() = default;

    virtual void update(const Core::IWindow& window, const float) override {}
    virtual void drawOutput(Core::IWindow&) override {}
private:
    std::unique_ptr<Gui::IUserInterface> gui;
};

}