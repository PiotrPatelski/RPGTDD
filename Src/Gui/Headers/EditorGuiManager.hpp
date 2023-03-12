#pragma once

#include <SFML/Window.hpp>
#include <GuiManager.hpp>
#include <ButtonBuilder.hpp>
#include <ButtonMenuBuilder.hpp>
#include <EditorGui.hpp>

namespace Gui
{

class EditorGuiManager : public GuiManager
{
public:
    EditorGuiManager(
        const sf::VideoMode& resolution,
        std::unique_ptr<ButtonBuilder> buttonBuilder,
        std::unique_ptr<ButtonMenuBuilder> pauseMenuBuilder)
        : buttonBuilder(std::move(buttonBuilder)),
          pauseMenuBuilder(std::move(pauseMenuBuilder)),
          resolution(resolution)
    {
        std::cout<<"EditorGuiManager"<<std::endl;
    }
    virtual ~EditorGuiManager(){}

    virtual std::unique_ptr<Gui::UserInterface> createGui(const sf::Font&) override;
private:
    PauseMenu createPauseMenu(const sf::Font&);
    Types::Background createPauseBackgroundShade();
    std::unique_ptr<ButtonList> createPauseMenuImpl(const sf::Font&);
    std::unique_ptr<ButtonBuilder> buttonBuilder;
    std::unique_ptr<ButtonMenuBuilder> pauseMenuBuilder;
    const sf::VideoMode resolution;
};

}