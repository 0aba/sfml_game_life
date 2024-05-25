#ifndef GAME_LIFE_MENU_PAGE_HPP
#define GAME_LIFE_MENU_PAGE_HPP

#include "Utils.hpp"
#include "./Page.hpp"
#include "../GUI/Button.hpp"


class MenuPage: public Page
{
private:
    my_gui::Button* textPlay;
    my_gui::Button* textSettings;
    my_gui::Button* textRules;
    my_gui::Button* textExit;
public:
    explicit MenuPage(sf::RenderWindow* window, TypePage* pageView);

    ~MenuPage();

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event) override;
};

#endif //GAME_LIFE_MENU_PAGE_HPP
