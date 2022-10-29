#pragma once

namespace Core
{

struct GraphicsData
{
	uint width;
    uint height;
    bool fullscreen;
	uint frameRateLimit;
	bool verticalSync;
	uint antialiasingLevel;
};

class IIniParser
{
public:
    IIniParser(){}
    virtual ~IIniParser(){}
    virtual GraphicsData fetchDataFromGraphicsFile() = 0;
private:

};

class IniParser : public IIniParser
{
public:
    IniParser(){}
    virtual ~IniParser(){}
    virtual GraphicsData fetchDataFromGraphicsFile() override;
private:

};

}