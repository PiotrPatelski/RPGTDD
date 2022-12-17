#include <MainMenuState.h>
#include <IniParser.h>
#include <ButtonBuilder.hpp>

namespace States
{

MainMenuState::MainMenuState(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::MainMenuAssetsManager> assetsManager)
    : State(gfxConfig, kbrdConfig, std::move(assetsManager))
{
    initBackground();
    initFont();
    initKeybinds();
}

void MainMenuState::initBackground()
{
    const auto& videoMode = graphicsConfig.resolution;
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
        State::keyboardConfig.mainMenuKeys,
        State::keyboardConfig.supportedKeys);
}

}