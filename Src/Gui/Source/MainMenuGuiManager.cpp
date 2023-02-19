#include <MainMenuGuiManager.hpp>
#include <MenuGui.hpp>
#include <State.hpp>

namespace Gui
{

std::unique_ptr<Gui::UserInterface> MainMenuGuiManager::createGui(const sf::Font& font)
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

void MainMenuGuiManager::addToGameButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("New Game", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(15.6f, 30.f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(),
        Events::ToGameState());
}

void MainMenuGuiManager::addToSettingsButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("Settings", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(15.6f, 40.f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(),
        Events::ToSettingsState());
}

void MainMenuGuiManager::addToEditorButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("Editor", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(15.6f, 50.f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(),
        Events::ToEditorState());
}

void MainMenuGuiManager::addExitButton(const sf::Font& font)
{
    gui->addButton(buttonBuilder->
            withTextContent(sf::Text("Exit", font)).
            atPosition(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(15.6f, 65.5f))).
            withSize(VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(13.f, 6.f))).
            build(), 
        Events::ToExitState());
}

}