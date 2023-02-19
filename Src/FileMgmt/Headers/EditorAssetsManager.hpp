#pragma once

#include <AssetsManager.hpp>

namespace FileMgmt
{

class EditorAssetsManager : public AssetsManager
{
public:
    EditorAssetsManager();
    virtual ~EditorAssetsManager(){}
    virtual const sf::Font& getFont(const std::string&) const override;
    virtual const sf::Texture* getTexture(const std::string&) const override;
private:
    virtual void fetchFontsFromFiles();
    virtual void fetchTexturesFromFiles();

};

}