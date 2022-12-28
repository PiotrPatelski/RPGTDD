#pragma once

#include <SFML/Window.hpp>
#include <IniParser.hpp>
#include <Config.hpp>

namespace Core
{

class ConfigManager
{
public:
	ConfigManager();
	virtual ~ConfigManager(){}

	void setGraphics(const FileMgmt::GraphicsConfig& newConfig){graphics = newConfig;}

	inline FileMgmt::GraphicsConfig getGraphics() const {return graphics;}
	inline FileMgmt::KeyboardConfig getKeyboard() const {return keyboard;}
private:
	FileMgmt::GraphicsConfig graphics;
	FileMgmt::KeyboardConfig keyboard;
};

}