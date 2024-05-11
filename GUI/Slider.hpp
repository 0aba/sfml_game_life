#ifndef MY_GUI_SLIDER_HPP
#define MY_GUI_SLIDER_HPP

#include "Widget.hpp"
#include "Utils.hpp"

namespace my_gui
{
    class Slider: public Widget
    {
    protected:
        sf::Sprite popupPointer;
        sf::Sprite pointer;
        sf::Sprite sliderLine;

        sf::Texture texturePopupPointer;
        sf::Texture texturePointer;
        sf::Texture textureSliderLine;

        sf::Font font;
        sf::Color textColor;
        sf::Text textMin;
        sf::Text textMax;
        sf::Text textPopup;

        float hOffsetPercentageViewPopup = .5f;

        int minValue = 0;
        int maxValue = 100;
        int value = minValue;

        void (*changeEvent)(sf::RenderWindow* window, my_gui::Widget* widget);

        TypeAction currentAction = TypeAction::Idle;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;
    public:
        Slider(char* pathFont,
               char* pathTextureSliderLine,
               char* pathTexturePointer,
               char* pathTexturePopupPointer,
               float hOffsetPercentageViewPopup,
               void (*changeEvent)(sf::RenderWindow* window, Widget* widget),
               sf::Color textColor,
               sf::Color idleColor,
               sf::Color hoverColor,
               sf::Color activeColor,
               int minValue,
               int maxValue
        );

        void loadFont(const char* pathFont);
        void setTextColor(sf::Color textColor);

        void setIdleColor(sf::Color idleColor);
        void setHoverColor(sf::Color hoverColor);
        void setActiveColor(sf::Color activeColor);

        void setChangeEvent(void (*changeEvent)(sf::RenderWindow* window, Widget* widget));

        void loadTexturePopupPointer(const char* path);
        void loadTexturePointer(const char* path);
        void loadTextureSliderLine(const char* path);

        void setHOffsetViewPopup(float offset);
        float getHOffsetViewPopup() const;

        void setValueMax(int value);
        int getValueMax() const;
        void setValueMin(int value);
        int getValueMin() const;

        void setValuePointer(int value);
        int getValuesPointer() const;

        void setViewState(bool state) override;
    };
}



#endif //MY_GUI_SLIDER_HPP
