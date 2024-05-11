#ifndef MY_GUI_CONTEXT_MENU_ELEMENT_HPP
#define MY_GUI_CONTEXT_MENU_ELEMENT_HPP

#include "Widget.hpp"
#include "Utils.hpp"


namespace my_gui
{
    class ContextMenuElement: public Widget
    {
    private:
        sf::Sprite background;
        sf::Texture backgroundTexture;
        sf::Sprite image;
        sf::Texture imageTexture;

        sf::Font font;
        sf::Color textColor;
        sf::Text text;

        TypeAction currentAction = TypeAction::Idle;
        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        void (*clickEvent)(sf::RenderWindow* window, Widget* widget){};
    public:
        ContextMenuElement(sf::RenderWindow& window,
                           sf::Vector2f size,
                           sf::Vector2f position,
                           char* pathBackgroundTexture,
                           char* pathImage,
                           char* pathFont,
                           sf::String text,
                           void (*clickEvent)(sf::RenderWindow* window, Widget* widget),
                           sf::Color textColor,
                           sf::Color idleColor,
                           sf::Color hoverColor,
                           sf::Color activeColor
        );

        void loadBackgroundTexture(char* path);
        void loadImage(char* path);

        void loadFont(const char* pathFont);
        void setTextColor(sf::Color textColor);
        void setText(sf::String text);
        sf::String getText();

        void setClickEvent(void (*clickEvent)(sf::RenderWindow* window, Widget* widget));

        void setIdleColor(sf::Color idleColor);
        void setHoverColor(sf::Color hoverColor);
        void setActiveColor(sf::Color activeColor);

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;
    };
}


#endif //MY_GUI_CONTEXT_MENU_ELEMENT_HPP
