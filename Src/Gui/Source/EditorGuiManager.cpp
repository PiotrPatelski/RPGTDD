#include <EditorGuiManager.hpp>
#include <State.hpp>
#include <ButtonMenu.hpp>

namespace Gui
{
std::unique_ptr<Gui::UserInterface> EditorGuiManager::createGui(const sf::Font& font)
{
    std::cout<<"EditorGuiManager::createGui"<<std::endl;

    auto gui = std::make_unique<Gui::EditorGui>();
    gui->addPauseMenu(createPauseMenu(font));

    std::cout<<"EditorGuiManager::createGui done"<<std::endl;
    return std::move(gui);
}

PauseMenu EditorGuiManager::createPauseMenu(const sf::Font& font)
{
    sf::RectangleShape screenShade;
    screenShade.setSize(sf::Vector2f(static_cast<float>(resolution.width),
									static_cast<float>(resolution.height)));
	screenShade.setFillColor(sf::Color(20, 20, 20, 100));

    const auto backgroundSize = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(20.f, 60.f));
    const auto backgroundPosition = VectorMath::ScreenPercentagePoint(resolution, sf::Vector2f(40.f, 15.f));

    auto menuImpl = pauseMenuBuilder->
        withTextContent(sf::Text("Game Paused!", font)).
        atPosition(backgroundPosition).
        withSize(backgroundSize).
        withSection(sf::Text("Save", font), std::monostate{}).
        withSection(sf::Text("Load", font), std::monostate{}).
        withSection(sf::Text("Exit", font), std::monostate{}).
        withSection(sf::Text("Resume", font), std::monostate{}).
        build();
    return PauseMenu(std::move(menuImpl), screenShade);
}

}