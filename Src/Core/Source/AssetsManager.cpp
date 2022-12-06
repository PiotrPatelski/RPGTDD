#include <AssetsManager.h>

namespace Core
{

std::string AssetsManager::buildPath = std::filesystem::current_path().string() + "/../build/";

void MainMenuAssetsManager::fetchTextureFromFile()
{
    const std::string texturePath = buildPath + "/Assets/Textures/MainMenu/menu.jpg";
    if(not mainMenuTexture.loadFromFile(texturePath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open texture file from given path: " + texturePath));
	}
    std::cout << "Initialized MainMenu Textures..." << std::endl;
}

const sf::Texture& MainMenuAssetsManager::getTexture()
{
    return mainMenuTexture;
}

void MainMenuAssetsManager::fetchFontFromFile()
{
    const std::string fontPath = buildPath + "/Assets/Fonts/MainMenu/xbones.ttf";
    if(not mainMenuFont.loadFromFile(fontPath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open texture file from given path: " + fontPath));
	}
    std::cout << "Initialized MainMenu Fonts..." << std::endl;
}

const sf::Font& MainMenuAssetsManager::getFont()
{
    return mainMenuFont;
}

}