#pragma once

#include <AssetsManager.hpp>

namespace FileMgmt
{

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

}