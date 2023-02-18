#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <EditorGuiManager.hpp>
#include <UserInterface.hpp>

namespace States
{

class EditorState : public State
{
public:
    EditorState(
        std::shared_ptr<Core::IConfigManager>,
        std::unique_ptr<FileMgmt::AssetsManager>,
        std::unique_ptr<Gui::GuiManager>);
    virtual ~EditorState() = default;

    virtual void update(const Core::IWindow&, const float) override;
    virtual void drawOutput(Core::IWindow&) override;
private:
    std::unique_ptr<Gui::UserInterface> gui;
};

}