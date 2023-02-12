#pragma once
#include <ButtonListBuilder.hpp>

namespace Gui
{

class DropDownListBuilder : public ButtonListBuilder
{
public:
    virtual ~DropDownListBuilder() = default;
    virtual DropDownListBuilder& withTextContent(const sf::Text&) override;
    virtual std::unique_ptr<ButtonList> build(std::unique_ptr<IButton>) override;
private:
    sf::Text textContent;
};

}