#include <MainMenuGuiManager.hpp>
#include <MenuGui.hpp>
#include <State.hpp>

namespace Gui
{

std::unique_ptr<Gui::UserInterface> MainMenuGuiManager::createGui(const std::shared_ptr<sf::Font> font)
{
    gui = std::make_unique<Gui::MenuGui>();
    std::cout<<"MainMenuGuiManager::createGui"<<std::endl;
    addToGameButton(font);
    addToSettingsButton(font);
    addToEditorButton(font);
    addExitButton(font);
    std::cout<<"MainMenuGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

void MainMenuGuiManager::addToGameButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("New Game").withFont(font).
            atPosition(15.6f, 30.f).withSize(13.f, 6.f).
            build(),
        Events::ToGameState());
}

void MainMenuGuiManager::addToSettingsButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("Settings").withFont(font).
            atPosition(15.6f, 40.f).withSize(13.f, 6.f).
            build(),
        Events::ToSettingsState());
}

void MainMenuGuiManager::addToEditorButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("Editor").withFont(font).
            atPosition(15.6f, 50.f).withSize(13.f, 6.f).
            build(),
        Events::ToEditorState());
}

void MainMenuGuiManager::addExitButton(const std::shared_ptr<sf::Font> font)
{
    gui->addButton(buttonBuilder->
            withTextContent("Exit").withFont(font).
            atPosition(15.6f, 65.5f).withSize(13.f, 6.f).
            build(), 
        Events::ToExitState());
}

}