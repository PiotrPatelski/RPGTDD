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
    AssetsManager();
    virtual ~AssetsManager(){}

    static void setBuildPath(const std::string& path) {buildPath = path;}
    virtual std::shared_ptr<sf::Font> getFont() const override;
    virtual std::shared_ptr<sf::Texture> getTexture() const override;
protected:
    static std::string buildPath;
    std::shared_ptr<sf::Font> buttonFont;
    std::shared_ptr<sf::Texture> backgroundTexture;
private:
    virtual void fetchFontFromFile();
    virtual void fetchTextureFromFile();
};

class MainMenuAssetsManager : public AssetsManager
{
public:
    MainMenuAssetsManager()
    : AssetsManager()
    {std::cout<<"MainMenuAssetsManager"<<std::endl;}
    virtual ~MainMenuAssetsManager(){}
};

class GameAssetsManager : public AssetsManager
{
public:
    GameAssetsManager()
    : AssetsManager()
    {std::cout<<"GameAssetsManager"<<std::endl;}
    virtual ~GameAssetsManager(){}
};

class EditorAssetsManager : public AssetsManager
{
public:
    EditorAssetsManager()
    : AssetsManager()
    {std::cout<<"EditorAssetsManager"<<std::endl;}
    virtual ~EditorAssetsManager(){}
};

class SettingsAssetsManager : public AssetsManager
{
public:
    SettingsAssetsManager()
    : AssetsManager()
    {std::cout<<"SettingsAssetsManager"<<std::endl;}
    virtual ~SettingsAssetsManager(){}
};

}