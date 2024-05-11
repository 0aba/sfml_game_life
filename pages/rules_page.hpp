#ifndef GAME_LIFE_RULES_PAGE_HPP
#define GAME_LIFE_RULES_PAGE_HPP

#include "Utils.hpp"


class RulesPage: public Page
{
private:
    sf::Text textRules;
    sf::Text textBack;
public:
    explicit RulesPage(TypePage& pageView);

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event, sf::Vector2i mousePosition) override;
    void close(sf::RenderWindow& window) override;
};


#endif //GAME_LIFE_RULES_PAGE_HPP
