#pragma once
#include <StateActions.hpp>
#include <Config.hpp>
#include <MouseEventListener.hpp>

namespace Events
{

class InputListener
{
public:
    InputListener(){}
    virtual ~InputListener(){}

    virtual std::optional<Events::StateAction> getKeyboardAction() const = 0;
    virtual std::optional<Events::StateAction> getMouseAction(const sf::Vector2i&) const = 0;
};

class MenuInputListener : public InputListener
{
public:
    MenuInputListener(const FileMgmt::KeyboardConfig& config)
    : keyboard(config.getMainMenuKeyboard())
    {}
    virtual ~MenuInputListener(){}

    virtual std::optional<Events::StateAction> getKeyboardAction() const override;
    virtual std::optional<Events::StateAction> getMouseAction(const sf::Vector2i&) const override {return std::nullopt;}
private:
    const FileMgmt::KeyMap& keyboard;
};

class EditorInputListener : public InputListener
{
public:
    EditorInputListener(const FileMgmt::KeyboardConfig& config, std::unique_ptr<Events::MouseEventListener> mouseHandler)
    : keyboard(config.getEditorKeyboard()),
      mouse(std::move(mouseHandler))
    {}
    virtual ~EditorInputListener(){}

    virtual std::optional<Events::StateAction> getKeyboardAction() const override;
    virtual std::optional<Events::StateAction> getMouseAction(const sf::Vector2i&) const override;
private:
    const FileMgmt::KeyMap& keyboard;
    std::unique_ptr<Events::MouseEventListener> mouse;
};

}