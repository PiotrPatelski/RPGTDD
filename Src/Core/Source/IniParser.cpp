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

GraphicsConfig IniParser::parseGraphicsConfig()
{
    auto sourceFile = std::move(findAndOpenFile("/Config/graphics.ini"));
    GraphicsConfig config;

    sourceFile >> config.gameTitle;
    sourceFile >> config.resolution.width 
        >> config.resolution.height;
    sourceFile >> config.fullscreen;
    sourceFile >> config.frameRateLimit;
    sourceFile >> config.verticalSync;
    sourceFile >> config.contextSettings.antialiasingLevel;
    sourceFile.close();

    return config;
}

SupportedKeys IniParser::parseKeyboardConfig()
{
    auto sourceFile = std::move(findAndOpenFile("/Config/keyboard.ini"));
    SupportedKeys target;

    std::string key = "";
    int keyValue = 0;
    while (sourceFile >> key >> keyValue)
        target.setKey(key, keyValue);
    sourceFile.close();

    return target;
}

MainMenuKeys IniParser::parseMainMenuKeys(const SupportedKeys& availableKeys)
{
    auto sourceFile = std::move(findAndOpenFile("/Config/mainmenu_keybinds.ini"));
    MainMenuKeys target;

    std::string key = "";
    std::string supportedKey = "";
    while (sourceFile >> key >> supportedKey)
        target.setKey(key, availableKeys.getKeys().at(supportedKey));

    sourceFile.close();
    return target;
}

}