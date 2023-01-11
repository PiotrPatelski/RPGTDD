#include <AssetsManager.hpp>

namespace FileMgmt
{

std::string AssetsManager::buildPath = std::filesystem::current_path().string() + "/../build/";

AssetsManager::AssetsManager()
{
    std::cout<<"AssetsManager"<<std::endl;
    buttonFont = std::make_shared<sf::Font>();
    fetchFontFromFile();
    backgroundTexture = std::make_shared<sf::Texture>();
    fetchTextureFromFile();
}

void AssetsManager::fetchTextureFromFile()
{
    const std::string texturePath = buildPath + "/Assets/Textures/MainMenu/menu.jpg";
    if(not backgroundTexture->loadFromFile(texturePath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open texture file from given path: " + texturePath));
	}
    std::cout << "Initialized MainMenu Textures..." << std::endl;
}

std::shared_ptr<sf::Texture> AssetsManager::getTexture() const
{
    return backgroundTexture;
}

void AssetsManager::fetchFontFromFile()
{
    const std::string fontPath = buildPath + "/Assets/Fonts/MainMenu/xbones.ttf";
    if(not buttonFont->loadFromFile(fontPath))
    {
        throw std::runtime_error(
            std::string("ERROR::cannot open font file from given path: " + fontPath));
	}
    std::cout << "Initialized MainMenu Fonts..." << std::endl;
}

std::shared_ptr<sf::Font> AssetsManager::getFont() const
{
    return buttonFont;
}

}