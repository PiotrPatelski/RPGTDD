#include <Engine.h>

namespace Core
{

IClock& Engine::getClock()
{
    return clock;
}
GraphicsConfig& Engine::getGraphicsConfig()
{
    return graphicsConfig;
}
KeyboardConfig& Engine::getKeyboardConfig()
{
    return keyboardConfig;
}

bool Engine::isWindowOpen()
{ 
    return window.isActive();
}

bool Engine::updateState()
{
    window.handleSfmlEvents(sfmlEvent);
    if(not stateMachine.isWorkDone())
    {
        stateMachine.update(window.isCurrentlyFocused(), clock.getDeltaTime());
        return true;
    }
    return false;
}

void Engine::closeWindow()
{
    window.close();

}

void Engine::displayRenderedFrame()
{    
    window.clear();
    window.displayWindow();
}

void Engine::launchWindow()
{
    window.openWithSettings(graphicsConfig);
}

void Engine::runInitialState()
{
    stateMachine.runState(std::make_unique<States::MainMenuState>());
}

}