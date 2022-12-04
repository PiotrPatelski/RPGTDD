#pragma once

#include <SFML/Graphics.hpp>

namespace Core
{

class IAssetsManager
{
public:
    IAssetsManager(){}
    virtual ~IAssetsManager(){}

    virtual void fetchFontFromFile() = 0;
    virtual void fetchTextureFromFile() = 0;

    virtual const sf::Font& getFont() = 0;
    virtual const sf::Texture& getTexture() = 0;
};

class AssetsManager : public IAssetsManager
{
public:
    AssetsManager(){}
    virtual ~AssetsManager(){}

    static void setBuildPath(const std::string& path) {buildPath = path;}
protected:
    static std::string buildPath;
};

class MainMenuAssetsManager : public AssetsManager
{
public:
    MainMenuAssetsManager(){}
    virtual ~MainMenuAssetsManager(){}

    virtual void fetchFontFromFile() override;
    virtual void fetchTextureFromFile() override;

    virtual const sf::Font& getFont() override;
    virtual const sf::Texture& getTexture() override;
private:
    sf::Font mainMenuFont;
    sf::Texture mainMenuTexture;
};

}