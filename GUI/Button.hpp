#ifndef MY_GUI_BUTTON_HPP
#define MY_GUI_BUTTON_HPP

#include "Widget.hpp"
#include "Utils.hpp"

namespace my_gui
{
    class Button: public Widget
    {
    private:
        sf::Sprite background;
        sf::Texture backgroundTexture;

        sf::Color textColor;
        sf::Font font;
        sf::Text text;

        void (*clickEvent)(sf::RenderWindow* window, Widget* widget){};

        TypeAction currentAction = TypeAction::Idle;
        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;
    public:
        Button(sf::RenderWindow& window,
               sf::Vector2f size,
               sf::Vector2f position,
               char* pathBackgroundTexture,
               char* pathFont,
               sf::String text,
               void (*clickEvent)(sf::RenderWindow* window, Widget* widget),
               sf::Color textColor,
               sf::Color idleColor,
               sf::Color hoverColor,
               sf::Color activeColor
        );

        void loadFont(const char* pathFont);
        void setTextColor(sf::Color textColor);
        void setText(sf::String text);
        sf::String getText();

        void setIdleColor(sf::Color idleColor);
        void setHoverColor(sf::Color hoverColor);
        void setActiveColor(sf::Color activeColor);

        void setClickEvent(void (*clickEvent)(sf::RenderWindow* window, Widget* widget));

        void loadBackgroundTexture(const char* path);

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;
    };
}

#endif //MY_GUI_BUTTON_HPP
