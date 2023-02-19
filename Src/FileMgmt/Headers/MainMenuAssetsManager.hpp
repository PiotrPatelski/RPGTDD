#pragma once

#include <AssetsManager.hpp>

namespace FileMgmt
{

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

}