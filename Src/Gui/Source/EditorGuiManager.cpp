#include <EditorGuiManager.hpp>
#include <State.hpp>
#include <ButtonMenu.hpp>
#include <TileSelector.hpp>

namespace Gui
{
std::unique_ptr<Gui::UserInterface> EditorGuiManager::createGui(const sf::Font& font)
{
    std::cout<<"EditorGuiManager::createGui"<<std::endl;

    auto gui = std::make_unique<Gui::EditorGui>(createPauseMenu(font), std::make_unique<TileSelector>());

    std::cout<<"EditorGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

PauseMenu EditorGuiManager::createPauseMenu(const sf::Font& font)
{
    return PauseMenu(createPauseMenuImpl(font), createPauseBackgroundShade());
}

Types::Background EditorGuiManager::createPauseBackgroundShade()
{
    const auto backgroundSize = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(100.f, 100.f));
    const auto backgroundPosition = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(0.f, 0.f));

    Types::Background screenShade(backgroundPosition, backgroundSize);
	screenShade.setFillColor(sf::Color(20, 20, 20, 100));
    return screenShade;
}

std::unique_ptr<ButtonList> EditorGuiManager::createPauseMenuImpl(const sf::Font& font)
{
    const auto menuSize = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(20.f, 60.f));
    const auto menuPosition = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(40.f, 15.f));

    return pauseMenuBuilder->
        withTextContent(sf::Text("Game Paused!", font)).
        atPosition(menuPosition).
        withSize(menuSize).
        withSection(sf::Text("Save", font), std::monostate{}).
        withSection(sf::Text("Load", font), std::monostate{}).
        withSection(sf::Text("Exit", font), Events::ExitMapState()).
        withSection(sf::Text("Resume", font), Events::Pause()).
        build();
}

}