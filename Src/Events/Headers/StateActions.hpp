#pragma once

namespace States
{
class MenuState;
}

namespace Events
{
using MenuAction = std::function<void(States::MenuState&)>;
// using GameStateAction = std::function<void(States::GameState&)>;
// using SettingsAction = std::function<void(States::SettingsState&)>;
// using EditorAction = std::function<void(States::EditorState&)>;

using StateAction = std::variant<
    MenuAction>;
    // GameStateAction,
    // SettingsAction,
    // EditorAction>;

struct ToMainMenuState
{
    void operator()(States::MenuState&);
};

struct ToGameState
{
    void operator()(States::MenuState&);
};

struct ToSettingsState
{
    void operator()(States::MenuState&);
};

struct ToEditorState
{
    void operator()(States::MenuState&);
};

struct ToExitState
{
    void operator()(States::MenuState&);
};

struct ApplySettings
{
    void operator()(States::MenuState&);
};

}