#include <MainMenuState.hpp>
#include <GameState.hpp>
#include <EditorState.hpp>
#include <SettingsState.hpp>
#include <IniParser.hpp>

namespace States
{

MainMenuState::MainMenuState(
    std::shared_ptr<Core::IConfigManager> config,
    std::unique_ptr<FileMgmt::MainMenuAssetsManager> assetsManager,
    std::unique_ptr<Gui::MainMenuGuiManager> guiManager)
    : State(
        config,
        std::move(assetsManager),
        std::move(guiManager))
{
    initBackground();
    initFont();
    buttons = this->guiManager->createButtons(*font);
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
    if (buttons.at("GAME_STATE")->isPressed())
	{
		nextState = std::make_unique<GameState>(
            config,
            std::make_unique<FileMgmt::GameAssetsManager>(),
            std::make_unique<Gui::GameGuiManager>(config->getGraphics().resolution));
        markAsDone();
        return;
	}
	if (buttons.at("SETTINGS_STATE")->isPressed())
	{
		nextState = std::make_unique<SettingsState>(
            config,
            std::make_unique<FileMgmt::SettingsAssetsManager>(),
            std::make_unique<Gui::SettingsGuiManager>(config->getGraphics().resolution));
        markAsDone();
        return;
	}
	if (buttons.at("EDITOR_STATE")->isPressed())
	{
		nextState = std::make_unique<EditorState>(
            config,
            std::make_unique<FileMgmt::EditorAssetsManager>(),
            std::make_unique<Gui::EditorGuiManager>(config->getGraphics().resolution));
        markAsDone();
        return;
	}
	if (buttons.at("EXIT_STATE")->isPressed())
    {
        nextState.reset();
        markAsDone();
        return;
    }
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