#include <AssetsManager.hpp>

namespace FileMgmt
{

std::string AssetsManager::buildPath = std::filesystem::current_path().string() + "/../build/";

MainMenuAssetsManager::MainMenuAssetsManager()
{
    std::cout<<"MainMenuAssetsManager"<<std::endl;
    mainMenuFont = std::make_shared<sf::Font>();
    fetchFontFromFile();
    mainMenuTexture = std::make_shared<sf::Texture>();
    fetchTextureFromFile();
}

void MainMenuAssetsManager::fetchTextureFromFile()
{
    const std::string texturePath = buildPath + "/Assets/Textures/MainMenu/menu.jpg";
    if(not mainMenuTexture->loadFromFile(texturePath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open texture file from given path: " + texturePath));
	}
    std::cout << "Initialized MainMenu Textures..." << std::endl;
}

std::shared_ptr<sf::Texture> MainMenuAssetsManager::getTexture() const
{
    return mainMenuTexture;
}

void MainMenuAssetsManager::fetchFontFromFile()
{
    const std::string fontPath = buildPath + "/Assets/Fonts/MainMenu/xbones.ttf";
    if(not mainMenuFont->loadFromFile(fontPath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open font file from given path: " + fontPath));
	}
    std::cout << "Initialized MainMenu Fonts..." << std::endl;
}

std::shared_ptr<sf::Font> MainMenuAssetsManager::getFont() const
{
    return mainMenuFont;
}

}