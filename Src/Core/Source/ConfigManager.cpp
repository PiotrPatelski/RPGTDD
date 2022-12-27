#include <ConfigManager.hpp>

namespace Core
{

ConfigManager::ConfigManager()
{
    IniParser parser;
    graphics = parser.parseGraphicsConfig();
    keyboard.supportedKeys = parser.parseKeyboardConfig();
    keyboard.mainMenuKeys = parser.parseMainMenuKeys(keyboard.supportedKeys);
}

}