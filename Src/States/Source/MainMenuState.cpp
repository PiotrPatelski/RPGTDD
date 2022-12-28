#include <MainMenuState.h>
#include <IniParser.hpp>
#include <ButtonBuilder.hpp>

namespace States
{

MainMenuState::MainMenuState(
    std::shared_ptr<Core::ConfigManager> config,
    std::unique_ptr<FileMgmt::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::MainMenuGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager))
{
    initBackground();
    initFont();
    buttons = State::guiManager->createButtons(*font);
}

void MainMenuState::initBackground()
{
    const auto& videoMode = config->getGraphics().resolution;
    background = std::make_shared<sf::RectangleShape>(
        sf::Vector2f(
            static_cast<float>(videoMode.width),
            static_cast<float>(videoMode.height)));
    background->setTexture(State::assetsManager->getTexture().get());
}

void MainMenuState::initFont()
{
    font = State::assetsManager->getFont();
}

void MainMenuState::update(const sf::Vector2i& mousePosOnWindow, const float deltaTime)
{
    for(auto& [_, button] : buttons)
        button->update(mousePosOnWindow);
}

void MainMenuState::drawOutput(Core::IWindow& window)
{
    window.draw(*background);
    for(const auto& [_, button] : buttons)
    {
        window.draw(button->getBackground());
        window.draw(button->getTextContent());
    }
}

}