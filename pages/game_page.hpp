#ifndef GAME_LIFE_GAME_PAGE_HPP
#define GAME_LIFE_GAME_PAGE_HPP


#include "Utils.hpp"

class GamePage : public Page
{
private:
    sf::Text textBack;
public:
    explicit GamePage(TypePage &pageView);

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event, sf::Vector2i mousePosition) override;
    void close(sf::RenderWindow& window) override;
};


#endif //GAME_LIFE_GAME_PAGE_HPP
