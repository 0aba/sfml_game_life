#ifndef GAME_LIFE_SETTINGS_PAGE_HPP
#define GAME_LIFE_SETTINGS_PAGE_HPP

#include "./Utils.hpp"

class SettingsPage : public Page
{
private:
    sf::Text textBack;
public:
    explicit SettingsPage(TypePage& pageView);

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event, sf::Vector2i mousePosition) override;
    void close(sf::RenderWindow& window) override;

};

#endif //GAME_LIFE_SETTINGS_PAGE_HPP
