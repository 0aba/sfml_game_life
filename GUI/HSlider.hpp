#ifndef MY_GUI_H_SLIDER_HPP
#define MY_GUI_H_SLIDER_HPP

#include "Slider.hpp"


namespace my_gui
{
    class HSlider: public Slider
    {
    public:
        HSlider(sf::RenderWindow& window,
                sf::Vector2f size,
                sf::Vector2f position,
                char* pathFont,
                char* pathTextureSliderLine,
                char* pathTexturePointer,
                char* pathTexturePopupPointer,
                float hOffsetPercentageViewPopup,
                OBJECT_GUI* contextCalled,
                void (*changeEvent)(OBJECT_GUI* contextCalled, Slider* thisSlider),
                sf::Color textColor,
                sf::Color idleColor,
                sf::Color hoverColor,
                sf::Color activeColor,
                int minValue,
                int maxValue
        );

        void setSize(sf::Vector2f size) override;
        void setPosition(sf::Vector2f position) override;
        void draw(sf::RenderWindow& window) override;
        void checkOnEvent(sf::Event event) override;
    };
}

#endif //MY_GUI_H_SLIDER_HPP
