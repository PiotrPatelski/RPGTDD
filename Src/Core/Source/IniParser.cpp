#include <IniParser.h>

namespace Core
{

void IniParser::parseFileTo(GraphicsConfig& config)
{
    std::string filePath(buildPath + "/Config/graphics.ini");
    std::ifstream targetFile(filePath);

    if(not targetFile.is_open())
    {
       throw std::runtime_error(
            std::string("ERROR::cannot open graphics INI file from given path: " + filePath));
    }

    targetFile >> config.gameTitle;
    targetFile >> config.resolution.width 
        >> config.resolution.height;
    targetFile >> config.fullscreen;
    targetFile >> config.frameRateLimit;
    targetFile >> config.verticalSync;
    targetFile >> config.contextSettings.antialiasingLevel;
    targetFile.close();
}

void IniParser::parseFileTo(KeyboardConfig& config)
{
    std::string filePath(buildPath + "/Config/keyboard.ini");
    std::ifstream targetFile(filePath);

    if(not targetFile.is_open())
    {
       throw std::runtime_error(
            std::string("ERROR::cannot open graphics INI file from given path: " + filePath));
    }
    std::string key = "";
    int keyValue = 0;
    while (targetFile >> key >> keyValue)
        config.supportedKeys[key] = keyValue;
    targetFile.close();
}

}