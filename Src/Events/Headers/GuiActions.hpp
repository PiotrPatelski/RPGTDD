#pragma once
#include <MenuGui.hpp>
#include <GameGui.hpp>
#include <EditorGui.hpp>

namespace Events
{

class GuiAction
{
public:
    GuiAction() = default;
    virtual ~GuiAction() = default;
    virtual void execute(Gui::MenuGui&) = 0;
    virtual void execute(Gui::GameGui&) = 0;
    virtual void execute(Gui::EditorGui&) = 0;
};

class TogglePause : public GuiAction
{
public:
    TogglePause() = default;
    virtual ~TogglePause() = default;
    virtual void execute(Gui::MenuGui&) override {}
    virtual void execute(Gui::GameGui& gui) override {}
    virtual void execute(Gui::EditorGui& gui) override {gui.togglePause();}
};

}