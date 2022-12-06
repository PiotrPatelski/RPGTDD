#include <IniParser.h>

namespace Core
{

std::string IniParser::buildPath = std::filesystem::current_path().string() + "/../build/";

std::ifstream IniParser::findAndOpenFile(const std::string& path)
{
    std::string filePath(buildPath + path);
    std::ifstream targetFile(filePath);

    if(not targetFile.is_open())
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open graphics INI file from given path: " + filePath));
    }
    return std::move(targetFile);
}

void IniParser::parseFileTo(GraphicsConfig& config)
{
    auto targetFile = std::move(findAndOpenFile("/Config/graphics.ini"));

    targetFile >> config.gameTitle;
    targetFile >> config.resolution.width 
        >> config.resolution.height;
    targetFile >> config.fullscreen;
    targetFile >> config.frameRateLimit;
    targetFile >> config.verticalSync;
    targetFile >> config.contextSettings.antialiasingLevel;
    targetFile.close();
}

void IniParser::parseFileTo(SupportedKeys& target)
{
    auto sourceFile = std::move(findAndOpenFile("/Config/keyboard.ini"));

    std::string key = "";
    int keyValue = 0;
    while (sourceFile >> key >> keyValue)
        target.setKey(key, keyValue);
    sourceFile.close();
}

void IniParser::parseFileTo(MainMenuKeys& target, const SupportedKeys& availableKeys)
{
    auto sourceFile = std::move(findAndOpenFile("/Config/mainmenu_keybinds.ini"));

    std::string key = "";
    std::string supportedKey = "";
    while (sourceFile >> key >> supportedKey)
        target.setKey(key, availableKeys.getKeys().at(supportedKey));
    sourceFile.close();
}

}