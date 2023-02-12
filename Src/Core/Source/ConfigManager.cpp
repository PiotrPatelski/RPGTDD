#include <ConfigManager.hpp>

namespace Core
{

ConfigManager::ConfigManager()
{
    FileMgmt::IniParser parser;
    graphics = parser.getGraphicsConfig();
    diff = graphics;
    keyboard.supportedKeys = parser.getKeyboardConfig();
    keyboard.mainMenuKeys = parser.getMainMenuKeys(keyboard.supportedKeys);
}

void ConfigManager::applyDiff()
{
    graphics = diff;
    FileMgmt::IniParser parser;
    parser.setGraphicsConfig(graphics);
}

}