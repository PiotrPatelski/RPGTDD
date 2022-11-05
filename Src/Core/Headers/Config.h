#pragma once

#include <SFML/Window.hpp>

namespace Core
{

struct GraphicsConfig
{
	std::string gameTitle;
	sf::VideoMode resolution;
	bool fullscreen;
	uint frameRateLimit;
	bool verticalSync;
	sf::ContextSettings contextSettings;
};

struct KeyboardConfig
{
	std::map<std::string, uint> supportedKeys;
};

}