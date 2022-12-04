#include <State.h>

namespace States
{

State::State(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
    : assetsManager(std::move(assetsManager)),
      gfxConfig{gfxConfig},
      kbrdConfig{kbrdConfig}
{

}

MainMenuState::MainMenuState(
    Core::GraphicsConfig& gfxConfig,
    Core::KeyboardConfig& kbrdConfig,
    std::unique_ptr<Core::IAssetsManager> assetsManager)
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