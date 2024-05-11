#ifndef GAME_LIFE_MENU_PAGE_HPP
#define GAME_LIFE_MENU_PAGE_HPP

#include "Utils.hpp"


class MenuPage: public Page
{
private:
    sf::Text textPlay;
    sf::Text textSettings;
    sf::Text textRules;
    sf::Text textExit;
public:
    explicit MenuPage(TypePage &pageView);

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event, sf::Vector2i mousePosition) override;
    void close(sf::RenderWindow& window) override;
};

#endif //GAME_LIFE_MENU_PAGE_HPP
