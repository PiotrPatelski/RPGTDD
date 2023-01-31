#pragma once
#include <DropDownList.hpp>

namespace Gui
{

class DropDownListBuilder
{
public:
    virtual ~DropDownListBuilder() = default;
    virtual DropDownListBuilder& withTextContent(const sf::Text&) = 0;
    virtual std::unique_ptr<DropDownList> build(std::unique_ptr<IButton>) = 0;
};

class MenuDropDownListBuilder : public DropDownListBuilder
{
public:
    virtual ~MenuDropDownListBuilder() = default;
    virtual MenuDropDownListBuilder& withTextContent(const sf::Text&) override;
    virtual std::unique_ptr<DropDownList> build(std::unique_ptr<IButton>) override;
private:
    sf::Text textContent;
};

}