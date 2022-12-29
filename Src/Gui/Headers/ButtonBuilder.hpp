#pragma once

#include <Button.hpp>

namespace Gui
{

uint calculateFontSize(const sf::VideoMode&);

class ScreenPercentage
{
public:
    ScreenPercentage(const sf::VideoMode& resolution)
    : screenWidth(resolution.width),
      screenHeight(resolution.height)
    {}
    ~ScreenPercentage(){}

    float toPixelsOnX(const float percentage){return std::floor(static_cast<float>(screenWidth) * percentage / 100.f);}
    float toPixelsOnY(const float percentage){return std::floor(static_cast<float>(screenHeight) * percentage / 100.f);}
private:
    uint screenWidth;
    uint screenHeight;
};

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
    std::string textContent;
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f size{0.f, 0.f};
    sf::Font font;
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
};

class GameButtonBuilder : public IButtonBuilder
{
public:
    GameButtonBuilder(const sf::VideoMode& videoMode){std::cout<<"GameButtonBuilder"<<std::endl;}
    virtual ~GameButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual std::unique_ptr<IButton> build() override {}
};
class EditorButtonBuilder : public IButtonBuilder
{
public:
    EditorButtonBuilder(const sf::VideoMode& videoMode){std::cout<<"EditorButtonBuilder"<<std::endl;}
    virtual ~EditorButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual std::unique_ptr<IButton> build() override {}
};

class SettingsButtonBuilder : public IButtonBuilder
{
public:
    SettingsButtonBuilder(const sf::VideoMode& videoMode){std::cout<<"SettingsButtonBuilder"<<std::endl;}
    virtual ~SettingsButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual std::unique_ptr<IButton> build() override {}
};

}