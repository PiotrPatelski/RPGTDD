#pragma once

#include <Button.hpp>
#include <ButtonActions.hpp>

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

    //TODO MOVE TO SEPARATE ActionBuildetClass
    virtual IButtonBuilder& withAction(const Events::StateChangeAction&) = 0;
    //
    virtual std::unique_ptr<IButton> build() = 0;
};

class ButtonBuilder : public IButtonBuilder
{
public:
    ButtonBuilder(const sf::VideoMode&);
    virtual ~ButtonBuilder(){}
protected:
    sf::VideoMode screenResolution;
};

class MainMenuButtonBuilder : public ButtonBuilder
{
public:
    MainMenuButtonBuilder(const sf::VideoMode&);
    virtual ~MainMenuButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override;
    virtual IButtonBuilder& atPosition(const float x, const float y) override;
    virtual IButtonBuilder& withSize(const float x, const float y) override;
    virtual IButtonBuilder& withFont(const sf::Font&) override;

    virtual IButtonBuilder& withAction(const Events::StateChangeAction&) override;

    virtual std::unique_ptr<IButton> build() override;

private:
    std::string textContent;
    sf::Vector2f position{0.f, 0.f};
    sf::Vector2f size{0.f, 0.f};
    sf::Font font;
    EventColor idleColors;
    EventColor hoverColors;
    EventColor activeColors;
    Events::StateChangeAction action;
};

class GameButtonBuilder : public ButtonBuilder
{
public:
    GameButtonBuilder(const sf::VideoMode&);
    virtual ~GameButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual IButtonBuilder& withAction(const Events::StateChangeAction&) override {};
    virtual std::unique_ptr<IButton> build() override {};
};
class EditorButtonBuilder : public ButtonBuilder
{
public:
    EditorButtonBuilder(const sf::VideoMode&);
    virtual ~EditorButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual IButtonBuilder& withAction(const Events::StateChangeAction&) override {};
    virtual std::unique_ptr<IButton> build() override {}
};

class SettingsButtonBuilder : public ButtonBuilder
{
public:
    SettingsButtonBuilder(const sf::VideoMode&);
    virtual ~SettingsButtonBuilder(){}

    virtual IButtonBuilder& withTextContent(const std::string& text) override {}
    virtual IButtonBuilder& atPosition(const float x, const float y) override {}
    virtual IButtonBuilder& withSize(const float x, const float y) override {}
    virtual IButtonBuilder& withFont(const sf::Font&) override {}
    virtual IButtonBuilder& withAction(const Events::StateChangeAction&) override {};
    virtual std::unique_ptr<IButton> build() override {}
};

}