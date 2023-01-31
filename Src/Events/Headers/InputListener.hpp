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

class InputListener : public IInputListener
{
public:
    InputListener(const FileMgmt::IKeyboardMap& config)
    : config(config)
    {}
    virtual ~InputListener(){}

    virtual std::optional<Events::StateAction> getActiveAction() const override;
private:
    const FileMgmt::IKeyboardMap& config;
};

}