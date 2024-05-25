#ifndef GAME_LIFE_GAME_WIDGET_HPP
#define GAME_LIFE_GAME_WIDGET_HPP

#include "../GUI/Widget.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/HSlider.hpp"
#include "../GUI/ContextMenuElement.hpp"
#include "../GUI/ContextMenu.hpp"
#include "./GameWidget.hpp"
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
    my_gui::Button* buttonRandom;
    my_gui::Button* buttonClear;
    static void clickButtonGame(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton);
    static void clickButtonRandom(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton);
    static void clickButtonClear(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton);
    std::jthread* runDeveloperLife;

    my_gui::HSlider* sliderSpeed;

    bool selected = false;
    my_gui::ContextMenu* contextMenuCell;

    Coords selectedCellCoord;
    static void changeCell(GameWidget* gameWidget, TypeCell type);

    Cell* livingCell;
    Cell* deadCell;
    Cell* wall;
    Cell* killingCell;
    Cell* lifeSupportCell;

public:
    static const short MIN_SLIDER_VALUE = 500; // .5 секунд
    static const short MAX_SLIDER_VALUE = 3000; // 3 секунды

    GameWidget(sf::RenderWindow* window,
               sf::Vector2f size,
               sf::Vector2f position,
               Game* game,
               u16 amountCellOnX,
               u16 amountCellOnY);

    ~GameWidget();

    void setAmountCellOnX(u16 amount);
    u16 getAmountCellOnX() const;

    void setAmountCellOnY(u16 amount);
    u16 getAmountCellOnY() const;

    void breakGame();

    void setSize(sf::Vector2f size) override;

    void setPosition(sf::Vector2f position) override;

    void setViewState(bool state) override;

    void draw(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event event) override;
};

#endif //GAME_LIFE_GAME_WIDGET_HPP
