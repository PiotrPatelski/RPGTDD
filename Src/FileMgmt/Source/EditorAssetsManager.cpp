#include <EditorAssetsManager.hpp>

namespace FileMgmt
{

EditorAssetsManager::EditorAssetsManager()
{
    std::cout<<"EditorAssetsManager"<<std::endl;
    fetchFontsFromFiles();
}

void EditorAssetsManager::fetchTexturesFromFiles()
{

    std::cout << "Initialized Editor Textures..." << std::endl;
}

const sf::Texture* EditorAssetsManager::getTexture(const std::string& objectName) const
{
    return textures.at(objectName).getContent();
}

void EditorAssetsManager::fetchFontsFromFiles()
{
    fonts.emplace("MENU_BUTTON", File<sf::Font>(buildPath + "/Assets/Fonts/MainMenu/xbones.ttf"));
    std::cout << "Initialized Editor Fonts..." << std::endl;
}

const sf::Font& EditorAssetsManager::getFont(const std::string& objectName) const
{
    return *(fonts.at(objectName).getContent());
}

}