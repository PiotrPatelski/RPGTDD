#pragma once
#include <ButtonList.hpp>

namespace Gui
{

class ButtonListBuilder
{
public:
    virtual ~ButtonListBuilder() = default;
    virtual ButtonListBuilder& withTextContent(const sf::Text&) = 0;
    virtual std::unique_ptr<ButtonList> build(std::unique_ptr<IButton>) = 0;
};

}