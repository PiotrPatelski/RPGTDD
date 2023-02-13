#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <IniParser.hpp>
#include <Window.hpp>

namespace States
{

MainMenuState::MainMenuState(
    std::shared_ptr<Core::IConfigManager> configManager,
    std::unique_ptr<FileMgmt::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::GuiManager> guiManager)
    : MenuState(
        configManager,
        std::move(assetsManager))
{
    initBackground();
    gui = guiManager->createGui(State::assetsManager->getFont());
}

void MainMenuState::initBackground()
{
    const auto& videoMode = configManager->getGraphics().resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture().get());
}

void MainMenuState::update(const Core::IWindow& window, const float deltaTime)
{
    gui->update(window.getMousePosition());
    auto action = gui->getActiveAction();
    if(action.has_value())
        get<Events::MenuAction>(action.value())(*this);
}

void MainMenuState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    gui->drawTo(window);
}

}