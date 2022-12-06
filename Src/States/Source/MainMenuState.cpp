#include <MainMenuState.h>

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
}

void MainMenuState::initBackground()
{
    const auto& videoMode = gfxConfig.resolution;
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

}