#pragma once

#include <IniParser.h>
#include <SFML/Window.hpp>

namespace Core
{

class IGraphicsConfig
{
public:
    IGraphicsConfig(){}
    virtual ~IGraphicsConfig(){}
    virtual void fetchSettingsFromFile(IIniParser&) = 0;

    virtual bool getFullscreen() const = 0;
    virtual bool getVerticalSync() const = 0;
    virtual uint getFrameRateLimit() const = 0;
    virtual std::string getGameTitle() const = 0;
    virtual sf::ContextSettings getContextSettings() const = 0;
    virtual sf::VideoMode getResolution() const = 0;
private:

};

class GraphicsConfig : public IGraphicsConfig
{
public:
    GraphicsConfig(){}
    virtual ~GraphicsConfig(){}
    virtual void fetchSettingsFromFile(IIniParser& parser) override;

    virtual bool getFullscreen() const override {return fullscreen;}
    virtual bool getVerticalSync() const override {return verticalSync;}
    virtual uint getFrameRateLimit() const override {return frameRateLimit;}
    virtual std::string getGameTitle() const override {return gameTitle;}
    virtual sf::ContextSettings getContextSettings() const override {return contextSettings;}
    virtual sf::VideoMode getResolution() const override {return resolution;}

private:
	bool fullscreen;
	bool verticalSync;
	uint frameRateLimit;
    std::string gameTitle;
    sf::VideoMode resolution;
	sf::ContextSettings contextSettings;
};

}