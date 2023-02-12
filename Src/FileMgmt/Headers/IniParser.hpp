#pragma once
#include <Config.hpp>

namespace FileMgmt
{

class IIniParser
{
public:
    IIniParser(){}
    virtual ~IIniParser(){}

    virtual GraphicsConfig getGraphicsConfig() = 0;
    virtual SupportedKeys getKeyboardConfig() = 0;
    virtual MainMenuKeys getMainMenuKeys(const SupportedKeys&) = 0;

    virtual void setGraphicsConfig(const GraphicsConfig&) = 0;
};

class IniParser : public IIniParser
{
public:
    IniParser(){}
    virtual ~IniParser(){}

    virtual GraphicsConfig getGraphicsConfig() override;
    virtual SupportedKeys getKeyboardConfig() override;
    virtual MainMenuKeys getMainMenuKeys(const SupportedKeys&) override;

    virtual void setGraphicsConfig(const GraphicsConfig&) override;
    static void setBuildPath(const std::string& path) {buildPath = path;}
private:
    std::ifstream openFileForPull(const std::string& path);
    std::ofstream openFileForPush(const std::string& path);
    static std::string buildPath;
};

}