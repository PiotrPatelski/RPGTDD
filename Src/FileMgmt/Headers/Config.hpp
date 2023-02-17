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

class KeyMap
{
public:
	virtual ~KeyMap(){};
	virtual const bool isPressedAt(const std::string& key) const = 0;
	virtual const uint getKey(const std::string& key) const = 0;
	virtual void setKey(const std::string& key, const uint val) = 0;
};

class KeyboardMap : public KeyMap
{
public:
	virtual ~KeyboardMap(){};
	virtual const bool isPressedAt(const std::string& key) const
	{return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keys.at(key)));}
	virtual const uint getKey(const std::string& key) const {return keys.at(key);}
	virtual void setKey(const std::string& key, const uint val)	{keys[key] = val;}
protected:
	std::map<std::string, uint> keys;
};

class KeyboardConfig
{
public:
	const KeyMap& getSupportedKeyboard() const {return *supportedKeys;}
	const KeyMap& getMainMenuKeyboard() const {return *mainMenuKeys;}
	void setSupportedKeyboard(std::unique_ptr<KeyMap> supportedKeys) {this->supportedKeys = std::move(supportedKeys);}
	void setMainMenuKeyboard(std::unique_ptr<KeyMap> mainMenuKeys) {this->mainMenuKeys = std::move(mainMenuKeys);}
private:
	std::unique_ptr<KeyMap> supportedKeys;
	std::unique_ptr<KeyMap> mainMenuKeys;
};
}