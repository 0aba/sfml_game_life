#ifndef GAME_LIFE_UTILS_HPP
#define GAME_LIFE_UTILS_HPP

#include <SFML/Graphics.hpp>


enum TypePage
{
    Menu     = 0,
    Game     = 1,
    Settings = 2,
    Rules    = 3,
    Exit     = 4
};

class Page // todo! change logic page
{
protected:
    TypePage& pageView;
    sf::Font font;
public:
    explicit Page(TypePage& pageView) : pageView(pageView) { };

    virtual void drawOnWindow(sf::RenderWindow& window) { };
    virtual void checkOnEvent(sf::Event& event, sf::Vector2i mousePosition) { };
    virtual void close(sf::RenderWindow& window) { };
};

const char FRONT_TEXT_PATH[] = "C:\\Users\\aba\\Desktop\\game_life\\resources_GUI\\arial.ttf";

#endif //GAME_LIFE_UTILS_HPP
