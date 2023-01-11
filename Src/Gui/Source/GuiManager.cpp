#include <GuiManager.hpp>
#include <State.hpp>

namespace Gui
{

std::vector<StateChangingButton> MainMenuGuiManager::createButtons(const sf::Font& font)
{
    buttons.push_back(StateChangingButton{
        buttonBuilder.
            withTextContent("New Game").withFont(font).
            atPosition(15.6f, 30.f).withSize(13.f, 6.f).
            build(),
        Events::ToGameState()});
    buttons.push_back(StateChangingButton{
        buttonBuilder.
            withTextContent("Settings").withFont(font).
            atPosition(15.6f, 40.f).withSize(13.f, 6.f).
            build(),
        Events::ToSettingsState()});
    buttons.push_back(StateChangingButton{
        buttonBuilder.
            withTextContent("Editor").withFont(font).
            atPosition(15.6f, 50.f).withSize(13.f, 6.f).
            build(),
        Events::ToEditorState()});
    buttons.push_back(StateChangingButton{
        buttonBuilder.
            withTextContent("Exit").withFont(font).
            atPosition(15.6f, 65.5f).withSize(13.f, 6.f).
            build(), 
        Events::ToExitState()});
    return std::move(buttons);
}

std::vector<StateChangingButton> SettingsGuiManager::createButtons(const sf::Font& font)
{
    buttons.push_back(StateChangingButton{
        buttonBuilder.
            withTextContent("Back").withFont(font).
            atPosition(55.f, 40.f).withSize(13.f, 6.f).
            build(),
        Events::ToMainMenuState()});

    return std::move(buttons);
}

}