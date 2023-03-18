#pragma once
#include <ButtonList.hpp>

namespace Core
{
class Window;
}

namespace Gui
{

class DropDownList : public ButtonList
{
public:
    DropDownList(const sf::Text&, std::unique_ptr<Button>, std::vector<ActionButton>&&);
    virtual ~DropDownList(){}

    virtual std::optional<Events::StateAction> getActiveAction() override;
    virtual inline VectorMath::ScreenPercentagePoint getPosition() const override {return initiatingButton.object->getPosition();}
    virtual inline VectorMath::ScreenPercentagePoint getSize() const override {return initiatingButton.object->getSize();}
    virtual void update(const sf::Vector2i&) override;
    virtual void drawTo(Types::Window&) override;
private:
    void onAction();
    void applyActiveSectionAction(std::vector<ActionButton>::iterator);
    void applyActiveSectionText(std::vector<ActionButton>::iterator);
    void updateSections(const sf::Vector2i&);
    void drawInitButton(Types::Window&);
    void drawSections(Types::Window&);
    ActionButton initiatingButton;
    std::vector<ActionButton> sections;
};

}