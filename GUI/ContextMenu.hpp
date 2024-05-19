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
        unsigned short createElement(char *pathBackgroundTexture,
                                     char *pathImage,
                                     char *pathFont,
                                     sf::String text,
                                     void (*clickEvent)(sf::RenderWindow* window, Widget* widget),
                                     sf::Color textColor,
                                     sf::Color idleColor,
                                     sf::Color hoverColor,
                                     sf::Color activeColor);
        ContextMenuElement* getElementAt(unsigned short index);
        void delElementAt(unsigned short index);
        unsigned short getIndexLastElement() const;

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;

        ~ContextMenu();
    };
}


#endif //MY_GUI_CONTEXTMENU_HPP
