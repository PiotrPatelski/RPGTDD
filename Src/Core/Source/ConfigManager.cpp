#include <ConfigManager.hpp>

namespace Core
{

ConfigManager::ConfigManager()
{
    FileMgmt::IniParser parser;
    graphics = parser.parseGraphicsConfig();
    keyboard.supportedKeys = parser.parseKeyboardConfig();
    keyboard.mainMenuKeys = parser.parseMainMenuKeys(keyboard.supportedKeys);
}

}