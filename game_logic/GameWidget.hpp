#ifndef GAME_LIFE_GAME_WIDGET_HPP
#define GAME_LIFE_GAME_WIDGET_HPP

#include "../GUI/Widget.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/HSlider.hpp"
#include "../GUI/ContextMenuElement.hpp"
#include "../GUI/ContextMenu.hpp"
#include "./Game.hpp"
#include <thread>


class GameWidget: public my_gui::Widget
{
private:
    Game game;
    sf::Vector2f sizeCell;

    u16 amountCellOnX;
    u16 amountCellOnY;

    bool gameRunStatus = false;
    my_gui::Button* buttonGame;
    void *(clickButtonGame)();
    void gameRuning(std::stop_token token);

    my_gui::HSlider* sliderSpeed;
    void onChangeSliderSpeed();

    bool selected = false;
    my_gui::ContextMenu* contextMenuCell;
    sf::Vector2f coordViewContextMenu;

    Coords selectedCellCoord;
    void onChangeCell(TypeCell type);

    void updateArena();

    TypeCell livingCell;
    TypeCell deadCell;
    TypeCell wall;
    TypeCell killingCell;
    TypeCell lifeSupportCell;

public:
    static const short MAX_SIDE_SIZE = 32;

    GameWidget(sf::Vector2f size,
               sf::Vector2f position,
               u16 amountCellOnX,
               u16 amountCellOnY);

    void setAmountCellOnX(u16 amount);
    u16 getAmountCellOnX() const;

    void setAmountCellOnY(u16 amount);
    u16 getAmountCellOnY() const;

    ~GameWidget();
};


#endif //GAME_LIFE_GAME_WIDGET_HPP
