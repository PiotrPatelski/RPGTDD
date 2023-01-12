#include <Engine.hpp>
#include <GuiManager.hpp>

namespace Core
{

Engine::Engine(const ICoreBuilder& builder)
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
            stateMachine->update(window->getMousePosition(), clock->getDeltaTime());
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

void Engine::runInitialState(std::shared_ptr<ConfigManager> configManager)
{
    stateMachine->setState(Events::ToMainMenuState()(configManager));
}

}