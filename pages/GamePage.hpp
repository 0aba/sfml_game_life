#ifndef GAME_LIFE_GAME_PAGE_HPP
#define GAME_LIFE_GAME_PAGE_HPP

#include "./Page.hpp"
#include "../GUI/Button.hpp"
#include "../game_logic/GameWidget.hpp"


class GamePage : public Page
{
private:
    my_gui::Button* backButton;
    GameWidget* gameWidget;
public:
    explicit GamePage(sf::RenderWindow* window, TypePage* pageView, Game* game);

    ~GamePage();

    GameWidget* getPtrOnGameWidget();

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event) override;
};

#endif //GAME_LIFE_GAME_PAGE_HPP
