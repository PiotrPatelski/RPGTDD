#include <DropDownListBuilder.hpp>
#include <DropDownList.hpp>
#include <ScreenPercentagePoint.hpp>
#include <SettingsListCalculator.hpp>

namespace Gui
{

DropDownListBuilder& DropDownListBuilder::withTextContent(const sf::Text& name)
{
    assert(triggerButton != nullptr);
    textContent = name;
    textContent.setPosition(VectorMath::SettingsListCalculator{}.textPositionOverButton(triggerButton->getPosition()));
    return *this;
}
DropDownListBuilder& DropDownListBuilder::withTriggerButton(std::unique_ptr<Button> triggerButton)
{
    this->triggerButton = std::move(triggerButton);
    return *this;
}

DropDownListBuilder& DropDownListBuilder::withSection(const std::optional<sf::Text> name, Events::StateAction action)
{
    assert(triggerButton != nullptr);

    sections.push_back(
        ActionButton{
            triggerButton->clone(name, getNextSectionPosition()),
            action});
    return *this;
}

std::unique_ptr<ButtonList> DropDownListBuilder::build()
{
    return std::make_unique<DropDownList>(textContent, std::move(triggerButton), std::move(sections));
}

VectorMath::ScreenPercentagePoint DropDownListBuilder::getNextSectionPosition() const
{
    if(sections.empty())
    {
        return VectorMath::SettingsListCalculator{}.calculatePositionBelow(
            triggerButton->getPosition(),
            triggerButton->getSize());
    }
    return VectorMath::SettingsListCalculator{}.calculatePositionBelow(
        sections.back().object->getPosition(),
        sections.back().object->getSize());
}

}