#include <DropDownListBuilder.hpp>
#include <DropDownList.hpp>

namespace Gui
{

DropDownListBuilder& DropDownListBuilder::withTextContent(const sf::Text& name)
{
    textContent = name;
    return *this;
}

std::unique_ptr<ButtonList> DropDownListBuilder::build(std::unique_ptr<IButton> initiatingButton)
{
    return std::make_unique<DropDownList>(textContent, std::move(initiatingButton));
}

}