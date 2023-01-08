#pragma once

#include <SFML/Window.hpp>
#include <ConfigManager.hpp>
#include <AssetsManager.hpp>
#include <GuiManager.hpp>
#include <Button.hpp>

namespace States
{
class IState;
}

namespace Events
{

class IInputHandler
{
public:
	IInputHandler(){}
	virtual ~IInputHandler(){}

    virtual const bool isStateReadyToChange() const = 0;
	virtual std::unique_ptr<States::IState> getNextStateOnActiveButton(const Gui::IButton&) = 0;
};

class InputHandler : public IInputHandler
{
public:
	InputHandler(std::shared_ptr<Core::IConfigManager>);
	virtual ~InputHandler(){}

    virtual const bool isStateReadyToChange() const override {return stateReadyToChange;}
protected:
    std::shared_ptr<Core::IConfigManager> configManager;
    bool stateReadyToChange{false};
};

class MainMenuInputHandler : public InputHandler
{
public:
	MainMenuInputHandler(std::shared_ptr<Core::IConfigManager>);
	virtual ~MainMenuInputHandler(){}

	virtual std::unique_ptr<States::IState> getNextStateOnActiveButton(const Gui::IButton&) override;
};

class GameInputHandler : public InputHandler
{
public:
	GameInputHandler(std::shared_ptr<Core::IConfigManager>);
	virtual ~GameInputHandler(){}

	virtual std::unique_ptr<States::IState> getNextStateOnActiveButton(const Gui::IButton&) override;
};

class EditorInputHandler : public InputHandler
{
public:
	EditorInputHandler(std::shared_ptr<Core::IConfigManager>);
	virtual ~EditorInputHandler(){}

	virtual std::unique_ptr<States::IState> getNextStateOnActiveButton(const Gui::IButton&) override;
};

class SettingsInputHandler : public InputHandler
{
public:
	SettingsInputHandler(std::shared_ptr<Core::IConfigManager>);
	virtual ~SettingsInputHandler(){}

	virtual std::unique_ptr<States::IState> getNextStateOnActiveButton(const Gui::IButton&) override;
};

}