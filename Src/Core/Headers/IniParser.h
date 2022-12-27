#pragma once
#include <Config.h>

namespace Core
{

class IIniParser
{
public:
    IIniParser(){}
    virtual ~IIniParser(){}

    virtual GraphicsConfig parseGraphicsConfig() = 0;
    virtual SupportedKeys parseKeyboardConfig() = 0;
    virtual MainMenuKeys parseMainMenuKeys(const SupportedKeys&) = 0;
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) = 0;
};

class IniParser : public IIniParser
{
public:
    IniParser(){}
    virtual ~IniParser(){}

    virtual GraphicsConfig parseGraphicsConfig() override;
    virtual SupportedKeys parseKeyboardConfig() override;
    virtual MainMenuKeys parseMainMenuKeys(const SupportedKeys&) override;

    static void setBuildPath(const std::string& path) {buildPath = path;}
private:
    virtual std::ifstream findAndOpenFile(const std::string& path) override;
    static std::string buildPath;
};

}