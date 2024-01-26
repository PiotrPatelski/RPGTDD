#include <ConfigManager.hpp>

namespace FileMgmt
{

ConfigManager::ConfigManager()
{
    FileMgmt::IniParser parser;
    graphics = parser.getGraphicsConfig();
    diff = graphics;
    keyboard.setSupportedKeyboard(parser.getKeyboardConfig());
    keyboard.setMainMenuKeyboard(parser.getMainMenuKeys(keyboard.getSupportedKeyboard()));
    keyboard.setEditorKeyboard(parser.getEditorKeys(keyboard.getSupportedKeyboard()));
    tileIds = parser.getTileIdConfig();
}

void ConfigManager::applyDiff()
{
    graphics = diff;
    FileMgmt::IniParser{}.overwriteGraphicsConfig(graphics);
}

}