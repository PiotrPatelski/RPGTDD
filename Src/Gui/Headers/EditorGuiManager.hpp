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
    EditorGuiManager(
        std::unique_ptr<IButtonBuilder> buttonBuilder,
        const sf::VideoMode& resolution)
        : buttonBuilder(std::move(buttonBuilder)),
          resolution(resolution)
    {
        std::cout<<"EditorGuiManager"<<std::endl;
    }
    virtual ~EditorGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const std::shared_ptr<sf::Font>) override;
private:
    std::unique_ptr<IButtonBuilder> buttonBuilder;
    const sf::VideoMode resolution;
};

}