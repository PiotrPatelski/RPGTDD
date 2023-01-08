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

std::unique_ptr<States::IState> MainMenuInputHandler::getNextStateOnActiveButton(const Gui::IButton& button)
{
    if(button.isPressed())
    {
        stateReadyToChange = true;
        return button.getAction()(configManager);
    }
    stateReadyToChange = false;
    return nullptr;
}

GameInputHandler::GameInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> GameInputHandler::getNextStateOnActiveButton(const Gui::IButton&)
{}

EditorInputHandler::EditorInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> EditorInputHandler::getNextStateOnActiveButton(const Gui::IButton&)
{}

SettingsInputHandler::SettingsInputHandler(std::shared_ptr<Core::IConfigManager> configManager)
: InputHandler(configManager)
{}

std::unique_ptr<States::IState> SettingsInputHandler::getNextStateOnActiveButton(const Gui::IButton&)
{}

}
