#ifndef MY_GUI_WIDGET_HPP
#define MY_GUI_WIDGET_HPP

#include <SFML/Graphics.hpp>


namespace my_gui
{
    class Widget
    {
    protected:
        sf::RenderWindow* window = nullptr;
        sf::Vector2f size;
        sf::Vector2f position;
        bool viewState = true;
    public:
        void setWindow(sf::RenderWindow& window);
        sf::RenderWindow* getWindow();

        virtual void setSize(sf::Vector2f size) = 0;
        sf::Vector2f getSize();

        virtual void setPosition(sf::Vector2f position) = 0;
        sf::Vector2f getPosition();

        virtual void setViewState(bool state) = 0;
        bool getViewState() const;

        virtual void draw(sf::RenderWindow& window) = 0;
        virtual void checkOnEvent(sf::Event event) = 0;
    };
};

#endif //MY_GUI_WIDGET_HPP
