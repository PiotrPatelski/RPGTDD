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

}