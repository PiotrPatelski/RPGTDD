#include <EditorGuiManager.hpp>
#include <State.hpp>
#include <ButtonMenu.hpp>

namespace Gui
{
std::unique_ptr<Gui::UserInterface> EditorGuiManager::createGui(const std::shared_ptr<sf::Font> font)
{
    auto gui = std::make_unique<Gui::EditorGui>();
    auto pauseMenu = std::make_unique<ButtonMenu>(
        "Game Paused!",
        font,
        resolution,
        sf::Vector2f{20.f, 60.f},
        sf::Vector2f{35.f, 15.f},
        std::move(buttonBuilder));
    pauseMenu->addSection("Save", std::monostate{});
    pauseMenu->addSection("Load", std::monostate{});
    pauseMenu->addSection("Exit", std::monostate{});
    pauseMenu->addSection("Resume", std::monostate{});
    gui->addPauseMenu(std::move(pauseMenu));
    return std::move(gui);
}

}