#include <ConfigManager.hpp>

namespace Core
{

ConfigManager::ConfigManager()
{
    FileMgmt::IniParser parser;
    graphics = parser.getGraphicsConfig();
    diff = graphics;
    keyboard.setSupportedKeyboard(parser.getKeyboardConfig());
    keyboard.setMainMenuKeyboard(parser.getMainMenuKeys(keyboard.getSupportedKeyboard()));
    keyboard.setEditorKeyboard(parser.getEditorKeys(keyboard.getSupportedKeyboard()));
}

void ConfigManager::applyDiff()
{
    graphics = diff;
    FileMgmt::IniParser parser;
    parser.setGraphicsConfig(graphics);
}

}