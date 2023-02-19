#pragma once
#include <ButtonListBuilder.hpp>
#include <ButtonBuilder.hpp>
#include <Background.hpp>


namespace Gui
{

class MenuButtonBuilder;

class ButtonMenuBuilder : public ButtonListBuilder
{
public:
    ButtonMenuBuilder();
    virtual ~ButtonMenuBuilder() = default;
    virtual ButtonMenuBuilder& withTextContent(const sf::Text&) override;
    virtual ButtonMenuBuilder& withTriggerButton(std::unique_ptr<Button>) override {return *this;}
    virtual ButtonMenuBuilder& withSection(const std::optional<sf::Text>, Events::StateAction) override;
    virtual ButtonMenuBuilder& atPosition(const VectorMath::ScreenPercentagePoint&);
    virtual ButtonMenuBuilder& withSize(const VectorMath::ScreenPercentagePoint&);
    virtual std::unique_ptr<ButtonList> build() override;
private:
    VectorMath::ScreenPercentagePoint calculateNextSectionPosition();
    Types::Background background{
        VectorMath::ScreenPercentagePoint{sf::VideoMode{1,1}, {0,0}},
        VectorMath::ScreenPercentagePoint{sf::VideoMode{1,1}, {0,0}}};
    MenuButtonBuilder buttonBuilder;
    sf::Text textContent;
    std::vector<ActionButton> sections;
    sf::VideoMode resolution;
};

}