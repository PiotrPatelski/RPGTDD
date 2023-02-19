#pragma once
#include <StateActions.hpp>
#include <Config.hpp>

namespace Events
{

class InputListener
{
public:
    InputListener(){}
    virtual ~InputListener(){}

    virtual std::optional<Events::StateAction> getActiveAction() const = 0;
};

class MenuInputListener : public InputListener
{
public:
    MenuInputListener(const FileMgmt::KeyboardConfig& config)
    : keyboard(config.getMainMenuKeyboard())
    {}
    virtual ~MenuInputListener(){}

    virtual std::optional<Events::StateAction> getActiveAction() const override;
private:
    const FileMgmt::KeyMap& keyboard;
};

class EditorInputListener : public InputListener
{
public:
    EditorInputListener(const FileMgmt::KeyboardConfig& config)
    : keyboard(config.getEditorKeyboard())
    {}
    virtual ~EditorInputListener(){}

    virtual std::optional<Events::StateAction> getActiveAction() const override;
private:
    const FileMgmt::KeyMap& keyboard;
};

}