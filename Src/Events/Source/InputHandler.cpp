#include <InputHandler.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>

namespace Events
{

InputHandler::InputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: configManager(configManager)
{}

MainMenuInputHandler::MainMenuInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> MainMenuInputHandler::getNextStateOnActiveButton(const Gui::StateChangingButton& button)
{
    if(button.object->isPressed())
    {
        stateReadyToChange = true;
        return button.action(configManager);
    }
    stateReadyToChange = false;
    return nullptr;
}

GameInputHandler::GameInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> GameInputHandler::getNextStateOnActiveButton(const Gui::StateChangingButton&)
{}

EditorInputHandler::EditorInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> EditorInputHandler::getNextStateOnActiveButton(const Gui::StateChangingButton&)
{}

SettingsInputHandler::SettingsInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> SettingsInputHandler::getNextStateOnActiveButton(const Gui::StateChangingButton&)
{}

}
