#include <DropDownListBuilder.hpp>

namespace Gui
{

MenuDropDownListBuilder& MenuDropDownListBuilder::withTextContent(const sf::Text& name)
{
    textContent = name;
    return *this;
}

std::unique_ptr<DropDownList> MenuDropDownListBuilder::build(std::unique_ptr<IButton> initiatingButton)
{
    return std::make_unique<MenuDropDownList>(textContent, std::move(initiatingButton));
}

}