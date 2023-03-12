#include <MainMenuAssetsManager.hpp>

namespace FileMgmt
{

MainMenuAssetsManager::MainMenuAssetsManager()
{
    std::cout<<"MainMenuAssetsManager"<<std::endl;
    fetchFontsFromFiles();
    fetchTexturesFromFiles();
}

void MainMenuAssetsManager::fetchTexturesFromFiles()
{
    textures.emplace("MENU_BACKGROUND", File<sf::Texture>(buildPath + "/Assets/Textures/Backgrounds/menu.jpg"));
    std::cout << "Initialized MainMenu Textures..." << std::endl;
}

const sf::Texture* MainMenuAssetsManager::getTexture(const std::string& objectName) const
{
    return textures.at(objectName).getContent();
}

void MainMenuAssetsManager::fetchFontsFromFiles()
{
    fonts.emplace("MENU_BUTTON", File<sf::Font>(buildPath + "/Assets/Fonts/MainMenu/xbones.ttf"));
    std::cout << "Initialized MainMenu Fonts..." << std::endl;
}

const sf::Font& MainMenuAssetsManager::getFont(const std::string& objectName) const
{
    return *(fonts.at(objectName).getContent());
}

}