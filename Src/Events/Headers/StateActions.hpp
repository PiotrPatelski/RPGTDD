#pragma once
#include <SFML/Window.hpp>

namespace States
{
class MenuState;
class MapState;
}

namespace Events
{
using MenuAction = std::function<void(States::MenuState&)>;
using GameAction = std::function<void(States::MapState&)>;

using StateAction = std::variant<
    std::monostate,
    MenuAction,
    GameAction>;

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

struct SetResolutionTo
{
    SetResolutionTo(const sf::VideoMode&);
    void operator()(States::MenuState&);
private:
    sf::VideoMode value;
};

struct Pause
{
    void operator()(States::MapState&);
};

struct ExitMapState
{
    void operator()(States::MapState&);
};

class AddTile
{
public:
    AddTile(const sf::Vector2i& currentMousePosition)
    : mousePosition(currentMousePosition)
    {}
    void operator()(States::MapState&){}
private:
    const sf::Vector2i mousePosition;
};

class RemoveTile
{
public:
    RemoveTile(const sf::Vector2i& currentMousePosition)
    : mousePosition(currentMousePosition)
    {}
    void operator()(States::MapState&){}
private:
    const sf::Vector2i mousePosition;
};

}