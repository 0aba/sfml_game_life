#ifndef GAME_LIFE_GAME_WIDGET_HPP
#define GAME_LIFE_GAME_WIDGET_HPP

#include "../GUI/Widget.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/HSlider.hpp"
#include "../GUI/ContextMenuElement.hpp"
#include "../GUI/ContextMenu.hpp"
#include "./Cell.hpp"
#include "./Game.hpp"
#include <thread>
#include <chrono>


class GameWidget: public my_gui::Widget
{
private:
    Game* game;
    sf::Vector2f sizeCell;

    u16 amountCellOnX;
    u16 amountCellOnY;

    bool gameRunStatus = false;
    my_gui::Button* buttonGame;
    static void clickButtonGame(Widget* contextCalled, my_gui::Button* thisButton);
    std::jthread* runDeveloperLife;

    my_gui::HSlider* sliderSpeed;

    bool selected = false;
    my_gui::ContextMenu* contextMenuCell;
    sf::Vector2f coordViewContextMenu;

    Coords selectedCellCoord;
    void changeCell(TypeCell type);

    Cell* livingCell;
    Cell* deadCell;
    Cell* wall;
    Cell* killingCell;
    Cell* lifeSupportCell;

public:
    static const short MIN_SLIDER_VALUE = 1;
    static const short MAX_SLIDER_VALUE = 100;

    GameWidget(sf::RenderWindow* window,
               sf::Vector2f size,
               sf::Vector2f position,
               u16 amountCellOnX,
               u16 amountCellOnY);

    ~GameWidget();

    void setAmountCellOnX(u16 amount);
    u16 getAmountCellOnX() const;

    void setAmountCellOnY(u16 amount);
    u16 getAmountCellOnY() const;

    void setSize(sf::Vector2f size) override;

    void setPosition(sf::Vector2f position) override;

    void setViewState(bool state) override;

    void draw(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event event) override;
};

#endif //GAME_LIFE_GAME_WIDGET_HPP
