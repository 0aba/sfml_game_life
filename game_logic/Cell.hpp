#ifndef GAME_LIFE_CELL_HPP
#define GAME_LIFE_CELL_HPP

#include "../GUI/Widget.hpp"


class Cell: public my_gui::Widget
{
private:
    sf::Sprite cellSprite;
    sf::Texture cellTexture;
public:
    Cell(sf::Vector2f size,
         sf::Vector2f position,
         char* pathCellTexture
         );

    void loadCellTexture(char* path);

    void setSize(sf::Vector2f size) override;

    void setPosition(sf::Vector2f position) override;
    void setViewState(bool state) override;

    void draw(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event event) override; /* todo! ??*/
};



#endif //GAME_LIFE_CELL_HPP
