#pragma once
#include <ButtonList.hpp>

namespace Gui
{

class ButtonListBuilder
{
public:
    virtual ~ButtonListBuilder() = default;
    virtual ButtonListBuilder& withTextContent(const sf::Text&) = 0;
    virtual ButtonListBuilder& withTriggerButton(std::unique_ptr<Button>) = 0;
    virtual ButtonListBuilder& withSection(const std::optional<sf::Text>, Events::StateAction) = 0;
    virtual std::unique_ptr<ButtonList> build() = 0;
};

}