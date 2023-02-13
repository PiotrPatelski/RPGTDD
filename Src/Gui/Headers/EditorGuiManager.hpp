#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
#include <ButtonBuilder.hpp>
#include <EditorGui.hpp>

namespace Gui
{

class EditorGuiManager : public GuiManager
{
public:
    EditorGuiManager(std::unique_ptr<IButtonBuilder> buttonBuilder)
        : buttonBuilder(std::move(buttonBuilder)){std::cout<<"EditorGuiManager"<<std::endl;}
    virtual ~EditorGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override {return std::make_unique<Gui::EditorGui>();}
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
};

}