#pragma once

#include <SFML/Window.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonListBuilder.hpp>
#include <UserInterface.hpp>

namespace Gui
{

class GuiManager
{
public:
    GuiManager(){}
    virtual ~GuiManager(){}
    
    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) = 0;
};

}