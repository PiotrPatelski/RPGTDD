#pragma once

namespace Core
{

struct GraphicsData
{
    std::string gameTitle;
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
    IniParser(const std::string& binaryPath)
    : binaryPath{binaryPath}
    {}
    virtual ~IniParser(){}
    virtual GraphicsData fetchDataFromGraphicsFile() override;
private:
    const std::string binaryPath;
};

}