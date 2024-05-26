#ifndef GAME_LIFE_SETTINGS_PAGE_HPP
#define GAME_LIFE_SETTINGS_PAGE_HPP

#include "./Utils.hpp"
#include "./Page.hpp"
#include "../game_logic/GameWidget.hpp"
#include "../GUI/HSlider.hpp"
#include "../GUI/Button.hpp"


class SettingsPage : public Page
{
private:
    GameWidget* gameWidget;

    sf::Font font;

    sf::Text titleAlive;
    static void changeAlivePercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderAlivePercent;
    sf::Text titleWall;
    static void changeWallPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderWallPercent;
    sf::Text titleSupport;
    static void changeSupportPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderSupportPercent;
    sf::Text titleKilling;
    static void changeKillingPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderKillingPercent;

    sf::Text titleAmountX;
    static void changeAmountX(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderAmountX;
    sf::Text titleAmountY;
    static void changeAmountY(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider);
    my_gui::HSlider* sliderAmountY;

    my_gui::Button* backButton;
public:
    explicit SettingsPage(sf::RenderWindow* window, TypePage* pageView, GameWidget* gameWidget);

    ~SettingsPage();

    void drawOnWindow(sf::RenderWindow& window) override;
    void checkOnEvent(sf::Event& event) override;
};

#endif //GAME_LIFE_SETTINGS_PAGE_HPP
