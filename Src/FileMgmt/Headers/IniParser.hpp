#pragma once
#include <Config.hpp>

namespace FileMgmt
{

class IniParser
{
public:
    IniParser(){}
    ~IniParser(){}

    GraphicsConfig getGraphicsConfig();
    std::unique_ptr<KeyMap> getKeyboardConfig();
    std::unique_ptr<KeyMap> getMainMenuKeys(const KeyMap&);
    std::unique_ptr<KeyMap> getEditorKeys(const KeyMap&);
    std::vector<std::string> getTileIdConfig();

    void overwriteGraphicsConfig(const GraphicsConfig&);
    static void setBuildPath(const std::string& path) {buildPath = path;}
private:
    std::ifstream openFileForPull(const std::string&);
    std::ofstream openFileForPush(const std::string&);
    std::unique_ptr<KeyMap> parseWithValidation(std::ifstream&, const KeyMap&);
    static std::string buildPath;
};

}