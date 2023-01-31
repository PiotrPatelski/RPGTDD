#pragma once

#include <SFML/Window.hpp>

namespace FileMgmt
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

class IKeyboardMap
{
public:
	virtual const std::map<std::string, uint>& getKeys() const = 0;
	virtual void setKey(const std::string&, const uint) = 0;
};

class KeyboardMap : public IKeyboardMap
{
public:
	virtual const std::map<std::string, uint>& getKeys() const override {return keys;}
	virtual void setKey(const std::string& key, const uint val) override
	{
		keys[key] = val;
	}
protected:
	std::map<std::string, uint> keys;
};

class SupportedKeys : public KeyboardMap
{};

class MainMenuKeys : public KeyboardMap
{};

struct KeyboardConfig
{
	SupportedKeys supportedKeys;
	MainMenuKeys mainMenuKeys;
};

}