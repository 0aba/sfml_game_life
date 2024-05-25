#ifndef GAME_LIFE_SETTINGS_PAGE_HPP
#define GAME_LIFE_SETTINGS_PAGE_HPP

#include "./Utils.hpp"
#include "./Page.hpp"
#include "../game_logic/Game.hpp"
#include "../GUI/HSlider.hpp"
#include "../GUI/Button.hpp"

class SettingsPage : public Page
{
private:
    // todo!!!!!!!!
    my_gui::Button* backButton;
public:
    explicit SettingsPage(sf::RenderWindow* window, TypePage* pageView, Game* game);

    ~SettingsPage();

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event) override;
};

#endif //GAME_LIFE_SETTINGS_PAGE_HPP
