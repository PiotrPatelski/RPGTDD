#include <GuiManager.hpp>

namespace Gui
{

std::map<std::string, std::unique_ptr<IButton>> MainMenuGuiManager::createButtons(const sf::Font& font)
{
    buttons["GAME_STATE"] = buttonBuilder.
        withTextContent("New Game").atPosition(15.6f, 30.f).withSize(13.f, 6.f).withFont(font).
        build();
    buttons["SETTINGS_STATE"] = buttonBuilder.
        withTextContent("Settings").atPosition(15.6f, 40.f).withSize(13.f, 6.f).withFont(font).
        build();
    buttons["EDITOR_STATE"] = buttonBuilder.
        withTextContent("Editor").atPosition(15.6f, 50.f).withSize(13.f, 6.f).withFont(font).
        build();
    buttons["EXIT_STATE"] = buttonBuilder.
        withTextContent("Exit").atPosition(15.6f, 65.5f).withSize(13.f, 6.f).withFont(font).
        build();
    return std::move(buttons);
}

}