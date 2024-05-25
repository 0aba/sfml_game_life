#ifndef GAME_LIFE_RULES_PAGE_HPP
#define GAME_LIFE_RULES_PAGE_HPP

#include "Utils.hpp"
#include "./Page.hpp"
#include "../GUI/Button.hpp"


class RulesPage: public Page
{
private:
    sf::Text textRules;
    sf::Font font;
    my_gui::Button* backButton;
public:
    explicit RulesPage(sf::RenderWindow* window, TypePage* pageView);

    ~RulesPage();

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event) override;
};


#endif //GAME_LIFE_RULES_PAGE_HPP
