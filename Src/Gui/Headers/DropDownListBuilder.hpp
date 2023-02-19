#pragma once
#include <ButtonListBuilder.hpp>

namespace Gui
{

class DropDownListBuilder : public ButtonListBuilder
{
public:
    DropDownListBuilder(){}
    virtual ~DropDownListBuilder() = default;
    virtual DropDownListBuilder& withTextContent(const sf::Text&) override;
    virtual DropDownListBuilder& withTriggerButton(std::unique_ptr<Button>) override;
    virtual DropDownListBuilder& withSection(const std::optional<sf::Text>, Events::StateAction) override;
    virtual std::unique_ptr<ButtonList> build() override;
private:
    VectorMath::ScreenPercentagePoint getNextSectionPosition() const;
    std::unique_ptr<Button> triggerButton;
    std::vector<ActionButton> sections;
    sf::Text textContent;
};
}