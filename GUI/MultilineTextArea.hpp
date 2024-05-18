#ifndef MY_GUI_MULTILINE_TEXT_AREA_HPP
#define MY_GUI_MULTILINE_TEXT_AREA_HPP

#include "Widget.hpp"


namespace my_gui
{
    class MultilineTextArea: public Widget
    {
    private:
        sf::String text;
        sf::Font font;
        sf::Color textColor;
        sf::Text viewText;

        unsigned short amountCharOnLine;
        unsigned short amountLines;
    public:
        MultilineTextArea(sf::RenderWindow& window,
                          sf::Vector2f size,
                          sf::Vector2f position,
                          char* pathFont,
                          sf::Color textColor,
                          sf::String text
                          );

        void loadFont(char* pathFont);
        void setTextColor(sf::Color textColor);
        void setText(sf::String text);
        sf::String getText();

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;

        void checkOnEvent(sf::Event event) override; /*todo! add events???*/
    };

}



#endif //MY_GUI_MULTILINE_TEXT_AREA_HPP
