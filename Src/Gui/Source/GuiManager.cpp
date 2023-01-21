#include <GuiManager.hpp>
#include <State.hpp>

namespace Gui
{

std::unique_ptr<Gui::UserInterface> MainMenuGuiManager::createGui(const std::shared_ptr<sf::Font> font)
{
    auto gui = std::make_unique<Gui::UserInterface>();
    std::cout<<"MainMenuGuiManager::createGui"<<std::endl;
    gui->addButton(buttonBuilder->
            withTextContent("New Game").withFont(font).
            atPosition(15.6f, 30.f).withSize(13.f, 6.f).
            build(),
        Events::ToGameState());
    gui->addButton(buttonBuilder->
            withTextContent("Settings").withFont(font).
            atPosition(15.6f, 40.f).withSize(13.f, 6.f).
            build(),
        Events::ToSettingsState());
    gui->addButton(buttonBuilder->
            withTextContent("Editor").withFont(font).
            atPosition(15.6f, 50.f).withSize(13.f, 6.f).
            build(),
        Events::ToEditorState());
    gui->addButton(buttonBuilder->
            withTextContent("Exit").withFont(font).
            atPosition(15.6f, 65.5f).withSize(13.f, 6.f).
            build(), 
        Events::ToExitState());
    std::cout<<"MainMenuGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

std::unique_ptr<Gui::UserInterface> SettingsGuiManager::createGui(const std::shared_ptr<sf::Font> font)
{
    auto gui = std::make_unique<Gui::UserInterface>();
    std::cout<<"SettingsGuiManager::createGui"<<std::endl;
    gui->addButton(buttonBuilder->
            withTextContent("Back").withFont(font).
            atPosition(72.f, 81.f).withSize(13.f, 6.f).
            build(),
        Events::ToMainMenuState());

    gui->addButton(buttonBuilder->
            withTextContent("Back").withFont(font).
            atPosition(55.f, 81.f).withSize(13.f, 6.f).
            build(),
        Events::ToMainMenuState());
    std::cout<<"SettingsGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

}