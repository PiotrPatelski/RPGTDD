#pragma once

#include <SFML/Graphics.hpp>

namespace FileMgmt
{

class IAssetsManager
{
public:
    IAssetsManager(){}
    virtual ~IAssetsManager(){}

    virtual std::shared_ptr<sf::Font> getFont() const = 0;
    virtual std::shared_ptr<sf::Texture> getTexture() const = 0;
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
    MainMenuAssetsManager();
    virtual ~MainMenuAssetsManager(){}

    virtual std::shared_ptr<sf::Font> getFont() const override;
    virtual std::shared_ptr<sf::Texture> getTexture() const override;
private:
    virtual void fetchFontFromFile();
    virtual void fetchTextureFromFile();

    std::shared_ptr<sf::Font> mainMenuFont;
    std::shared_ptr<sf::Texture> mainMenuTexture;
};

}