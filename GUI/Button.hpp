#ifndef MY_GUI_BUTTON_HPP
#define MY_GUI_BUTTON_HPP

#include "Widget.hpp"
#include "MultilineTextArea.hpp"
#include "Utils.hpp"

namespace my_gui
{
    class Button: public Widget
    {
    private:
        sf::Sprite background;
        sf::Texture backgroundTexture;

        my_gui::MultilineTextArea* text;

        OBJECT_GUI* contextCalled;
        void (*clickEvent)(OBJECT_GUI* contextCalled, Button* thisButton);

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
               OBJECT_GUI* contextCalled,
               void (*clickEvent)(OBJECT_GUI* contextCalled, Button* thisButton),
               sf::Color textColor,
               sf::Color idleColor,
               sf::Color hoverColor,
               sf::Color activeColor
        );

        ~Button();

        void loadFont(char* pathFont);
        void setTextColor(sf::Color textColor);
        void setText(sf::String text);
        sf::String getText();

        void setIdleColor(sf::Color idleColor);
        void setHoverColor(sf::Color hoverColor);
        void setActiveColor(sf::Color activeColor);

        void setClickEvent(void (*clickEvent)(OBJECT_GUI* contextCalled, Button* thisButton), OBJECT_GUI* contextCalled);

        void loadBackgroundTexture(char* path);

        void setSize(sf::Vector2f size) override;

        void setPosition(sf::Vector2f position) override;
        void setViewState(bool state) override;

        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;
    };
}

#endif //MY_GUI_BUTTON_HPP
