#pragma once

namespace States
{
class IState;
}
namespace Core
{
class IConfigManager;
}
namespace Events
{

class GameInputHandler;
using StateChangeAction = std::function<std::unique_ptr<States::IState>(std::shared_ptr<Core::IConfigManager> configManager)>;

struct ToMainMenuState
{
    std::unique_ptr<States::IState> operator()(std::shared_ptr<Core::IConfigManager> configManager);
};

struct ToGameState
{
    std::unique_ptr<States::IState> operator()(std::shared_ptr<Core::IConfigManager> configManager);
};

struct ToSettingsState
{
    std::unique_ptr<States::IState> operator()(std::shared_ptr<Core::IConfigManager> configManager);
};

struct ToEditorState
{
    std::unique_ptr<States::IState> operator()(std::shared_ptr<Core::IConfigManager> configManager);
};

struct ToExitState
{
    std::unique_ptr<States::IState> operator()(std::shared_ptr<Core::IConfigManager> configManager);
};

}