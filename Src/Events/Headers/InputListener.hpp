#pragma once
#include <StateActions.hpp>
#include <Config.hpp>

namespace Events
{

class IInputListener
{
public:
    IInputListener(){}
    virtual ~IInputListener(){}

    virtual std::optional<Events::StateAction> getActiveAction() const = 0;
};

class MenuInputListener : public IInputListener
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

}