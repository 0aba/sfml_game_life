#ifndef MY_GUI_CONTEXTMENU_HPP
#define MY_GUI_CONTEXTMENU_HPP

#include "Widget.hpp"
#include "ContextMenuElement.hpp"
#include <list>


namespace my_gui
{
    class ContextMenu: public Widget
    {
    private:
        sf::Sprite background;
        sf::Texture backgroundTexture;

        unsigned short lastElement;
        std::list<ContextMenuElement*> elements;
        sf::Vector2f elementSize;
    public:
        ContextMenu(sf::RenderWindow& window,
                    sf::Vector2f size,
                    sf::Vector2f position,
                    char* pathBackgroundTexture);

        void loadBackgroundTexture(char* path);

        unsigned short createElement();
        ContextMenuElement* getElementAt(unsigned short index);
        void delElementAt(unsigned short index);

        void freeMemoryWidget();

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;
    };
}


#endif //MY_GUI_CONTEXTMENU_HPP
