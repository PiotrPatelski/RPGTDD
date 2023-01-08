#include <GuiManager.hpp>
#include <State.hpp>

namespace Gui
{

std::vector<std::unique_ptr<IButton>> MainMenuGuiManager::createButtons(const sf::Font& font)
{
    buttons.push_back(buttonBuilder.
        withTextContent("New Game").atPosition(15.6f, 30.f).withSize(13.f, 6.f).withFont(font).
        withAction(Events::ToGameState()).build());
    buttons.push_back(buttonBuilder.
        withTextContent("Settings").atPosition(15.6f, 40.f).withSize(13.f, 6.f).withFont(font).
        withAction(Events::ToSettingsState()).build());
    buttons.push_back(buttonBuilder.
        withTextContent("Editor").atPosition(15.6f, 50.f).withSize(13.f, 6.f).withFont(font).
        withAction(Events::ToEditorState()).build());
    buttons.push_back(buttonBuilder.
        withTextContent("Exit").atPosition(15.6f, 65.5f).withSize(13.f, 6.f).withFont(font).
        withAction(Events::ToExitState()). build());
    return std::move(buttons);
}

}