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
    virtual std::unique_ptr<KeyMap> getKeyboardConfig() = 0;
    virtual std::unique_ptr<KeyMap> getMainMenuKeys(const KeyMap&) = 0;
    virtual std::unique_ptr<KeyMap> getEditorKeys(const KeyMap&) = 0;

    virtual void setGraphicsConfig(const GraphicsConfig&) = 0;
};

class IniParser : public IIniParser
{
public:
    IniParser(){}
    virtual ~IniParser(){}

    virtual GraphicsConfig getGraphicsConfig() override;
    virtual std::unique_ptr<KeyMap> getKeyboardConfig() override;
    virtual std::unique_ptr<KeyMap> getMainMenuKeys(const KeyMap&) override;
    virtual std::unique_ptr<KeyMap> getEditorKeys(const KeyMap&) override;

    virtual void setGraphicsConfig(const GraphicsConfig&) override;
    static void setBuildPath(const std::string& path) {buildPath = path;}
private:
    std::ifstream openFileForPull(const std::string&);
    std::ofstream openFileForPush(const std::string&);
    std::unique_ptr<KeyMap> parseWithValidation(std::ifstream&, const KeyMap&);
    static std::string buildPath;
};

}