#include <ConfigManager.hpp>

namespace Core
{

ConfigManager::ConfigManager()
{
    FileMgmt::IniParser parser;
    graphics = parser.parseGraphicsConfig();
    diff = graphics;
    keyboard.supportedKeys = parser.parseKeyboardConfig();
    keyboard.mainMenuKeys = parser.parseMainMenuKeys(keyboard.supportedKeys);
}

}