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

    virtual bool getFullscreen() = 0;
    virtual bool getVerticalSync() = 0;
    virtual uint getFrameRateLimit() = 0;
    virtual uint getAntialiasingLevel() = 0;
    virtual sf::VideoMode getResolution() = 0;
private:

};

class GraphicsConfig : public IGraphicsConfig
{
public:
    GraphicsConfig(){}
    virtual ~GraphicsConfig(){}
    virtual void fetchSettingsFromFile(IIniParser& parser) override;

    virtual bool getFullscreen() override {return fullscreen;}
    virtual bool getVerticalSync() override {return verticalSync;}
    virtual uint getFrameRateLimit() override {return frameRateLimit;}
    virtual uint getAntialiasingLevel() override {return contextSettings.antialiasingLevel;}
    virtual sf::VideoMode getResolution() override {return resolution;}

private:
    sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	uint frameRateLimit;
	sf::ContextSettings contextSettings;
};

}