#ifndef GAME_LIFE_GAME_WIDGET_HPP
#define GAME_LIFE_GAME_WIDGET_HPP

#include "../GUI/Widget.hpp"
#include "../GUI/Button.hpp"
#include "./Game.hpp"
#include <thread>


class GameWidget: public my_gui::Widget
{
private:
    Game game;
    sf::Vector2f sizeCell;

    unsigned short amountCellOnX;
    unsigned short amountCellOnY;

    bool gameRunStatus = false;
    my_gui::Button buttonGame;
    void *(clickButtonGame)();
    void gameRuning(std::stop_token token);

    // todo!!!!!!!!!!!!!!
    // ...
    // ...
    // ...
public:
    // todo!!!!!!!!!!!!!!
    // ...
    // ...
    // ...
};


#endif //GAME_LIFE_GAME_WIDGET_HPP
