#ifndef MY_GUI_CONTEXTMENU_HPP
#define MY_GUI_CONTEXTMENU_HPP

#include "Widget.hpp"
#include "ContextMenuElement.hpp"

namespace my_gui
{
    class ContextMenu: public Widget
    {
    private:
        sf::Sprite background;
        sf::Texture backgroundTexture;

        unsigned short maxAmountElements;
#       define EMPTY_ARRAY (-1)
        short lastElement = EMPTY_ARRAY;
        ContextMenuElement** elements = nullptr;
        sf::Vector2f elementSize;
    public:
        ContextMenu(sf::RenderWindow& window,
                    sf::Vector2f size,
                    sf::Vector2f position,
                    char* pathBackgroundTexture,
                    unsigned short maxAmountElements);

        void loadBackgroundTexture(char* path);

        void setMaxAmountElements(unsigned short amount);
        unsigned short getMaxAmountElements() const;

#       define NOT_FOUND_ELEMENT (-1)
#       define MAX_AMOUNT_ELEMENTS 32767
        unsigned short addElement(ContextMenuElement* element);
        unsigned short createDefaultElement();
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
