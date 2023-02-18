#include <EditorGuiManager.hpp>
#include <State.hpp>
#include <ButtonMenu.hpp>

namespace Gui
{
std::unique_ptr<Gui::UserInterface> EditorGuiManager::createGui(const sf::Font& font)
{
    auto gui = std::make_unique<Gui::EditorGui>();
    auto pauseMenu = std::make_unique<ButtonMenu>(
        "Game Paused!",
        font,
        resolution,
        sf::Vector2f{20.f, 60.f},
        sf::Vector2f{35.f, 15.f},
        std::move(buttonBuilder));
    pauseMenu->addSection(sf::Text("Save", font), std::monostate{});
    pauseMenu->addSection(sf::Text("Load", font),std::monostate{});
    pauseMenu->addSection(sf::Text("Exit", font),std::monostate{});
    pauseMenu->addSection(sf::Text("Resume", font),std::monostate{});
    gui->addPauseMenu(std::move(pauseMenu));
    return std::move(gui);
}

}