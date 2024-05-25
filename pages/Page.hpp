#ifndef GAME_LIFE_PAGE_HPP
#define GAME_LIFE_PAGE_HPP

#include "./Utils.hpp"
#include "../GUI/OBJECT_GUI.hpp"

class Page: public my_gui::OBJECT_GUI
{
protected:
    sf::RenderWindow* window;
    TypePage* pageView;
public:
    explicit Page(sf::RenderWindow* window, TypePage* pageView);

    void setWindow(sf::RenderWindow* window);
    sf::RenderWindow* getWindow();

    virtual void drawOnWindow(sf::RenderWindow& window) = 0;
    virtual void checkOnEvent(sf::Event& event) = 0;
};


#endif //GAME_LIFE_PAGE_HPP
