#include <Engine.hpp>
#include <GuiManager.hpp>

namespace Core
{

Engine::Engine(const CoreBuilder& builder)
: 
window(builder.createWindow()),
clock(builder.createClock()),
stateMachine(builder.createStateMachine())
{}

void Engine::updateDeltaTime()
{
    clock->updateDeltaTime();
}

bool Engine::isWindowOpen()
{ 
    return window->isActive();
}

bool Engine::updateState()
{
    window->handleSfmlEvents(sfmlEvent);
    if(stateMachine->isAnyStateActive())
    {
        if(window->isCurrentlyFocused())
        {
            stateMachine->update(*window, clock->getDeltaTime());
        }
        return true;
    }
    return false;
}

void Engine::closeWindow()
{
    window->close();

}

void Engine::displayRenderedFrame()
{    
    window->clear();
    if(stateMachine->isAnyStateActive())
        stateMachine->getCurrentState()->drawOutput(*window);
    window->display();
}

void Engine::launchWindow(const FileMgmt::GraphicsConfig& config)
{
    window->openWithSettings(config);
}

void Engine::runInitialState(std::shared_ptr<FileMgmt::IConfigManager> configManager)
{
    stateMachine->setState(
        std::make_shared<States::MainMenuState>(
            configManager,
            std::make_unique<FileMgmt::MainMenuAssetsManager>(),
            std::make_unique<Gui::MainMenuGuiManager>(
                configManager->getGraphics().resolution,
                std::make_unique<Gui::MenuButtonBuilder>()
            )));
}

}