#pragma once

#include <Button.hpp>

namespace Gui
{

class IButtonBuilder
{
public:
    IButtonBuilder(){}
    virtual ~IButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string&) = 0;
    virtual IButtonBuilder& atPosition(const float, const float) = 0;
    virtual IButtonBuilder& withSize(const float, const float) = 0;
    virtual IButtonBuilder& withFont(const sf::Font&) = 0;
    virtual std::unique_ptr<IButton> build() = 0;
};

class MainMenuButtonBuilder : public IButtonBuilder
{
public:
    MainMenuButtonBuilder(const sf::VideoMode&);
    virtual ~MainMenuButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override;
    virtual IButtonBuilder& atPosition(const float x, const float y) override;
    virtual IButtonBuilder& withSize(const float x, const float y) override;
    virtual IButtonBuilder& withFont(const sf::Font&) override;
    virtual std::unique_ptr<IButton> build() override;

private:
    sf::VideoMode screenResolution;
    std::string textContent = "";
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f size{0.f, 0.f};
    sf::Font font;
};

}