#pragma once

#include <Config.h>

namespace Core
{

class IIniParser
{
public:
    IIniParser(){}
    virtual ~IIniParser(){}

    virtual void parseFileTo(GraphicsConfig&) = 0;
    virtual void parseFileTo(SupportedKeys&) = 0;
    virtual void parseFileTo(MainMenuKeys&, const SupportedKeys&) = 0;
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) = 0;
};

class IniParser : public IIniParser
{
public:
    IniParser(){}
    virtual ~IniParser(){}

    virtual void parseFileTo(GraphicsConfig&) override;
    virtual void parseFileTo(SupportedKeys&) override;
    virtual void parseFileTo(MainMenuKeys&, const SupportedKeys&) override;

    static void setBuildPath(const std::string& path) {buildPath = path;}
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) override;
    static std::string buildPath;
};

}