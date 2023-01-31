#pragma once

#include <SFML/Window.hpp>
#include <IniParser.hpp>
#include <Config.hpp>

namespace Core
{

class IConfigManager
{
public:
	IConfigManager(){}
	virtual ~IConfigManager(){}

	virtual void setGraphics(const FileMgmt::GraphicsConfig&) = 0;

	virtual const FileMgmt::GraphicsConfig& getGraphics() const = 0;
	virtual const FileMgmt::KeyboardConfig& getKeyboard() const = 0;
};

class ConfigManager : public IConfigManager
{
public:
	ConfigManager();
	virtual ~ConfigManager(){}

	virtual inline void setGraphics(const FileMgmt::GraphicsConfig& newConfig) override {graphics = newConfig;}

	virtual inline const FileMgmt::GraphicsConfig& getGraphics() const override {return graphics;}
	virtual inline const FileMgmt::KeyboardConfig& getKeyboard() const override {return keyboard;}
private:
	FileMgmt::GraphicsConfig graphics;
	FileMgmt::KeyboardConfig keyboard;
};

}