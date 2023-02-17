#include <IniParser.hpp>

namespace FileMgmt
{

std::string IniParser::buildPath = std::filesystem::current_path().string() + "/../build/";

std::ifstream IniParser::openFileForPull(const std::string& path)
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

std::ofstream IniParser::openFileForPush(const std::string& path)
{
    std::string filePath(buildPath + path);
    std::ofstream targetFile(filePath);

    if(not targetFile.is_open())
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open graphics INI file from given path: " + filePath));
    }
    return std::move(targetFile);
}

void IniParser::setGraphicsConfig(const GraphicsConfig& config)
{
    auto sourceFile = std::move(openFileForPush("/Config/graphics.ini"));

    sourceFile << config.gameTitle << "\n";
    sourceFile << config.resolution.width
        << " " << config.resolution.height << "\n";
    sourceFile << config.fullscreen << "\n";
    sourceFile << config.frameRateLimit << "\n";
    sourceFile << config.verticalSync << "\n";
    sourceFile << config.contextSettings.antialiasingLevel;

    sourceFile.close();
}

GraphicsConfig IniParser::getGraphicsConfig()
{
    auto sourceFile = std::move(openFileForPull("/Config/graphics.ini"));
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

std::unique_ptr<KeyMap> IniParser::getKeyboardConfig()
{
    auto sourceFile = std::move(openFileForPull("/Config/keyboard.ini"));
    auto target = std::make_unique<KeyboardMap>();

    std::string key = "";
    int keyValue = 0;
    while (sourceFile >> key >> keyValue)
        target->setKey(key, keyValue);
    sourceFile.close();

    return std::move(target);
}

std::unique_ptr<KeyMap> IniParser::getMainMenuKeys(const KeyMap& availableKeys)
{
    auto sourceFile = std::move(openFileForPull("/Config/mainmenu_keybinds.ini"));
    auto target = std::make_unique<KeyboardMap>();

    std::string key = "";
    std::string supportedKey = "";
    while (sourceFile >> key >> supportedKey)
        target->setKey(key, availableKeys.getKey(supportedKey));

    sourceFile.close();
    return std::move(target);
}

}