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

class GameAssetsManager : public AssetsManager
{
public:
    GameAssetsManager(){std::cout<<"GameAssetsManager"<<std::endl;}
    virtual ~GameAssetsManager(){}

    virtual std::shared_ptr<sf::Font> getFont() const override {return std::make_shared<sf::Font>();}
    virtual std::shared_ptr<sf::Texture> getTexture() const override {return std::make_shared<sf::Texture>();}
};

class EditorAssetsManager : public AssetsManager
{
public:
    EditorAssetsManager(){std::cout<<"EditorAssetsManager"<<std::endl;}
    virtual ~EditorAssetsManager(){}

    virtual std::shared_ptr<sf::Font> getFont() const override {return std::make_shared<sf::Font>();}
    virtual std::shared_ptr<sf::Texture> getTexture() const override {return std::make_shared<sf::Texture>();}
};

class SettingsAssetsManager : public AssetsManager
{
public:
    SettingsAssetsManager(){std::cout<<"SettingsAssetsManager"<<std::endl;}
    virtual ~SettingsAssetsManager(){}

    virtual std::shared_ptr<sf::Font> getFont() const override {return std::make_shared<sf::Font>();}
    virtual std::shared_ptr<sf::Texture> getTexture() const override {return std::make_shared<sf::Texture>();}
};

}