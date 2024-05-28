#include "Slider.hpp"


my_gui::Slider::Slider(char *pathFont,
                       char *pathTextureSliderLine,
                       char *pathTexturePointer,
                       char *pathTexturePopupPointer,
                       float hOffsetPercentageViewPopup,
                       OBJECT_GUI* contextCalled,
                       void (*changeEvent)(OBJECT_GUI* contextCalled, Slider* thisSlider),
                       sf::Color textColor,
                       sf::Color idleColor,
                       sf::Color hoverColor,
                       sf::Color activeColor,
                       int minValue,
                       int maxValue)
{
    this->loadFont(pathFont);

    this->loadTextureSliderLine(pathTextureSliderLine);
    this->loadTexturePointer(pathTexturePointer);
    this->loadTexturePopupPointer(pathTexturePopupPointer);

    this->setHOffsetViewPopup(hOffsetPercentageViewPopup);
    this->setChangeEvent(changeEvent, contextCalled);

    this->setTextColor(textColor);
    this->setIdleColor(idleColor);
    this->setHoverColor(hoverColor);
    this->setActiveColor(activeColor);

    this->setValueMin(minValue);
    this->setValueMax(maxValue);
}

void my_gui::Slider::loadFont(char* pathFont)
{
    if(pathFont != nullptr && this->font.loadFromFile(pathFont)) { }
    else if (!this->font.loadFromFile("resources_GUI\\arial.ttf")) { return; }

    this->textMin.setFont(font);
    this->textMax.setFont(font);
    this->textPopup.setFont(font);
}

void my_gui::Slider::setTextColor(sf::Color textColor)
{
    this->textColor = textColor;
    this->textMin.setFillColor(this->textColor);
    this->textMax.setFillColor(this->textColor);
    this->textPopup.setFillColor(this->textColor);
}

void my_gui::Slider::setIdleColor(sf::Color idleColor) { this->idleColor = idleColor; }

void my_gui::Slider::setHoverColor(sf::Color hoverColor) { this->hoverColor = hoverColor; }

void my_gui::Slider::setActiveColor(sf::Color activeColor) { this->activeColor = activeColor; }

void my_gui::Slider::setChangeEvent(void (*changeEvent)(OBJECT_GUI* contextCalled, Slider* thisSlider), OBJECT_GUI* contextCalled)
{
    this->contextCalled = contextCalled;
    this->changeEvent = changeEvent;
}

void my_gui::Slider::loadTexturePopupPointer(char* path)
{
    if(path != nullptr && this->texturePopupPointer.loadFromFile(path)) { }
    else if (!this->texturePopupPointer.loadFromFile("resources_GUI\\slider_popup.png")) { return; }

    popupPointer.setTexture(this->texturePopupPointer);
}

void my_gui::Slider::loadTexturePointer(char* path)
{
    if(path != nullptr && this->texturePointer.loadFromFile(path)) { }
    else if (!this->texturePointer.loadFromFile("resources_GUI\\slider_pointer.png")) { return; }

    pointer.setTexture(this->texturePointer);
}

void my_gui::Slider::loadTextureSliderLine(char* path)
{
    if(path != nullptr && this->textureSliderLine.loadFromFile(path)) { }
    else if (!this->textureSliderLine.loadFromFile("resources_GUI\\slider_line.png")) { return; }

    sliderLine.setTexture(this->textureSliderLine);
}

void my_gui::Slider::setHOffsetViewPopup(float offset) { this->hOffsetPercentageViewPopup = offset; }

float my_gui::Slider::getHOffsetViewPopup() const { return this->hOffsetPercentageViewPopup; }

void my_gui::Slider::setValueMax(int value)
{
    this->maxValue = value;
    this->textMax.setString(std::to_string(this->getValueMax()));
}
int my_gui::Slider::getValueMax() const { return this->maxValue; }

void my_gui::Slider::setValueMin(int value)
{
    this->minValue = value;
    this->textMin.setString(std::to_string(this->getValueMin()));
}
int my_gui::Slider::getValueMin() const { return this->minValue; }

void my_gui::Slider::setOnlyValuePointer(int value)
{
    this->value = value;
    if (this->getValuesPointer() <= this->getValueMin()) { this->value = this->getValueMin(); }
    else if (this->getValuesPointer() >= this->getValueMax()) { this->value = this->getValueMax(); }

    this->textPopup.setString(std::to_string(this->getValuesPointer()));
}
int my_gui::Slider::getValuesPointer() const { return this->value; }

void my_gui::Slider::setViewState(bool state) { this->viewState = state; }
