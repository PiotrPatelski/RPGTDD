#pragma once

#include <SFML/Window.hpp>
#include <IniParser.h>
#include <Config.h>

namespace Core
{

class ConfigManager
{
public:
	ConfigManager();
	virtual ~ConfigManager(){}

	void setGraphics(const GraphicsConfig& newConfig){graphics = newConfig;}

	GraphicsConfig getGraphics(){return graphics;}
	KeyboardConfig getKeyboard(){return keyboard;}
private:
	GraphicsConfig graphics;
	KeyboardConfig keyboard;
};

}