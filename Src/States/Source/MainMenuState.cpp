#include <MainMenuState.h>
#include <IniParser.h>
#include <ButtonBuilder.hpp>

namespace States
{

MainMenuState::MainMenuState(
    Core::Config& config,
    std::unique_ptr<Core::MainMenuAssetsManager> assetsManager)
    : State(config, std::move(assetsManager))
{
    initBackground();
    initFont();
    initKeybinds();
}

void MainMenuState::initBackground()
{
    const auto& videoMode = config.graphics.resolution;
    background.setSize(sf::Vector2f(
        static_cast<float>(videoMode.width),
        static_cast<float>(videoMode.height)));
    State::assetsManager->fetchTextureFromFile();
    background.setTexture(&(State::assetsManager->getTexture()));
}

void MainMenuState::initFont()
{
    State::assetsManager->fetchFontFromFile();
    font = State::assetsManager->getFont();
}

void MainMenuState::initKeybinds()
{
    Core::IniParser{}.parseFileTo(
        State::config.keyboard.mainMenuKeys,
        State::config.keyboard.supportedKeys);
}

}