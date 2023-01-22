#pragma once

namespace States
{
class IState;
class MainMenuState;
class GameState;
class SettingsState;
class EditorState;
}

namespace Events
{
using MainMenuAction = std::function<void(States::MainMenuState&)>;
using GameStateAction = std::function<void(States::GameState&)>;
using SettingsAction = std::function<void(States::SettingsState&)>;
using EditorAction = std::function<void(States::EditorState&)>;

using StateAction = std::variant<
    MainMenuAction,
    GameStateAction,
    SettingsAction,
    EditorAction>;

struct ToMainMenuState
{
    void operator()(States::SettingsState&);
};

struct ToGameState
{
    void operator()(States::MainMenuState&);
};

struct ToSettingsState
{
    void operator()(States::MainMenuState&);
};

struct ToEditorState
{
    void operator()(States::MainMenuState&);
};

struct ToExitState
{
    void operator()(States::MainMenuState&);
};

struct ApplySettings
{
    void operator()(States::SettingsState&);
};

}