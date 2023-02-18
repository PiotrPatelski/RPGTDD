#pragma once

#include <SFML/Graphics.hpp>

namespace FileMgmt
{

template <typename Type>
class File
{
public:
    File(const std::string& path) {fetchFromFile(path);}
    const Type* getContent() const {return &content;}
private:
    void fetchFromFile(const std::string& path)
    {
        if(not content.loadFromFile(path))
        {
            throw std::runtime_error(
                std::string("ERROR::cannot open file from given path: " + path));
        }
    }
    Type content;
};

class AssetsManager
{
public:
    AssetsManager(){}
    virtual ~AssetsManager(){}
    static void setBuildPath(const std::string& path) {buildPath = path;}
    virtual const sf::Font& getFont(const std::string&) const = 0;
    virtual const sf::Texture* getTexture(const std::string&) const = 0;
protected:
    static std::string buildPath;
    std::map<std::string, File<sf::Font>> fonts;
    std::map<std::string, File<sf::Texture>> textures;
};

class MainMenuAssetsManager : public AssetsManager
{
public:
    MainMenuAssetsManager();
    virtual ~MainMenuAssetsManager(){}
    virtual const sf::Font& getFont(const std::string&) const override;
    virtual const sf::Texture* getTexture(const std::string&) const override;
private:
    virtual void fetchFontsFromFiles();
    virtual void fetchTexturesFromFiles();
};

class GameAssetsManager : public AssetsManager
{
public:
    GameAssetsManager()
    : AssetsManager()
    {std::cout<<"GameAssetsManager"<<std::endl;}
    virtual ~GameAssetsManager(){}
    virtual const sf::Font& getFont(const std::string&) const override {return font;}
    virtual const sf::Texture* getTexture(const std::string&) const override {return nullptr;}
private:
    sf::Font font;
};

class EditorAssetsManager : public AssetsManager
{
public:
    EditorAssetsManager()
    : AssetsManager()
    {std::cout<<"EditorAssetsManager"<<std::endl;}
    virtual ~EditorAssetsManager(){}
    virtual const sf::Font& getFont(const std::string&) const override {return font;}
    virtual const sf::Texture* getTexture(const std::string&) const override {return nullptr;}
private:
    sf::Font font;
};

}