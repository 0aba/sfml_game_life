#include "HSlider.hpp"
#include <cmath>


my_gui::HSlider::HSlider(sf::RenderWindow &window,
                         sf::Vector2f size,
                         sf::Vector2f position,
                         char *pathFont,
                         char *pathTextureSliderLine,
                         char *pathTexturePointer,
                         char *pathTexturePopupPointer,
                         float hOffsetPercentageViewPopup,
                         void (*changeEvent)(sf::RenderWindow *, Widget *),
                         sf::Color textColor,
                         sf::Color idleColor,
                         sf::Color hoverColor,
                         sf::Color activeColor,
                         int minValue,
                         int maxValue) : Slider(pathFont,
                                                pathTextureSliderLine,
                                                pathTexturePointer,
                                                pathTexturePopupPointer,
                                                hOffsetPercentageViewPopup,
                                                changeEvent,
                                                textColor,
                                                idleColor,
                                                hoverColor,
                                                activeColor,
                                                minValue,
                                                maxValue)
{
    this->setWindow(window);

    // просто this тоже работает, но так нет уведомлений от ide
    ((HSlider*) this)->setSize(size);
    ((HSlider*) this)->setPosition(position);
}

void my_gui::HSlider::setSize(sf::Vector2f size)
{
    this->size = size;
    this->sliderLine.setScale(this->getSize().x / this->textureSliderLine.getSize().x,
                              this->getSize().y / this->textureSliderLine.getSize().y);

    this->textMin.setCharacterSize(std::ceil(this->textureSliderLine.getSize().y * this->sliderLine.getScale().y * .75f));
    this->textMax.setCharacterSize(this->textMin.getCharacterSize());

    this->textPopup.setCharacterSize(this->textMin.getCharacterSize());

    // todo! error resize !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /// this->pointer.getScale().x Остается старым !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    this->pointer.setScale( this->getSize().y * .5f / this->texturePointer.getSize().x,
                            this->getSize().y * 1.5f / this->texturePointer.getSize().y);


    int minValueSize = std::to_string(this->getValueMin()).size();
    int maxValueSize = std::to_string(this->getValueMax()).size();

    this->popupPointer.setScale(this->textPopup.getCharacterSize() * .75f *
                                (minValueSize > maxValueSize ? minValueSize : maxValueSize) / this->texturePopupPointer.getSize().y,
                                this->textPopup.getCharacterSize() * 1.5f / this->texturePopupPointer.getSize().y );
    this->setPosition(this->position);
}

void my_gui::HSlider::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->sliderLine.setPosition(this->getPosition());

    this->textMin.setPosition(this->getPosition().x -
                              this->textMin.getString().getSize() * this->textMin.getCharacterSize() * .25f,
                              this->getPosition().y - this->textMin.getCharacterSize() * 1.5f);
    this->textMax.setPosition(this->getPosition().x -
                              this->textMin.getString().getSize() * this->textMin.getCharacterSize() * .25f +
                              this->textureSliderLine.getSize().x * this->sliderLine.getScale().x,
                              this->getPosition().y - this->textMax.getCharacterSize() * 1.5f);

    this->pointer.setPosition(this->getPosition().x +
                              this->textureSliderLine.getSize().x * this->sliderLine.getScale().x *
                              std::abs(this->getValueMin() - this->getValuesPointer()) /
                              std::abs(this->getValueMin() - this->getValueMax()) -
                              this->texturePointer.getSize().x * this->pointer.getScale().x * .5f,
                              this->getPosition().y -
                              this->getSize().y * .25f);

    this->popupPointer.setPosition(this->pointer.getPosition().x -
                                   this->texturePopupPointer.getSize().x * this->popupPointer.getScale().x * this->getHOffsetViewPopup() +
                                   this->texturePointer.getSize().x * this->pointer.getScale().x * .5f,
                                   this->pointer.getPosition().y -
                                   this->texturePopupPointer.getSize().y * this->popupPointer.getScale().y * 1.25f);


    this->textPopup.setPosition(this->popupPointer.getPosition().x +
                           (this->textPopup.getString().getSize() * this->textPopup.getCharacterSize() * .1f),
                           this->popupPointer.getPosition().y +
                           this->getSize().y * .5f -
                           this->textPopup.getCharacterSize() * .5f);
}

void my_gui::HSlider::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    this->setWindow(window);

    if (this->currentAction == TypeAction::Activated) { this->pointer.setColor(this->activeColor); }
    else if (this->currentAction == TypeAction::Hover) { this->pointer.setColor(this->hoverColor); }
    else /*(this->currentAction == TypeAction::Idle)*/ { this->pointer.setColor(this->idleColor); }

    this->window->draw(this->sliderLine);
    this->window->draw(this->pointer);
    this->window->draw(this->textMin);
    this->window->draw(this->textMax);

    if (currentAction == TypeAction::Idle) { return; }

    this->window->draw(this->popupPointer);
    this->window->draw(this->textPopup);
}

void my_gui::HSlider::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
        &&
        (this->currentAction == TypeAction::Activated
        ||
        this->pointer.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                 sf::Mouse::getPosition(*this->getWindow()).y)))
    {
        this->currentAction = TypeAction::Activated;

        unsigned short mousePosition = sf::Mouse::getPosition(*this->getWindow()).x;
        unsigned short pointerPosition = this->pointer.getPosition().x +
                                         this->texturePointer.getSize().x * this->pointer.getScale().x * .5f;

        int step = (std::abs(pointerPosition - mousePosition) / this->getSize().x) *
                   std::abs(this->getValueMin() - this->getValueMax());

        if (mousePosition == pointerPosition) { return; }

        else if (mousePosition < pointerPosition) { this->value -= step; }
        else /*(mousePosition > pointerPosition)*/ { this->value += step; }

        if (this->getValuesPointer() <= this->getValueMin()) { this->setValuePointer(this->getValueMin()); }
        else if (this->getValuesPointer() >= this->getValueMax()) { this->setValuePointer(this->getValueMax()); }

        this->setValuePointer(this->getValuesPointer());
        this->setPosition(this->getPosition());

        changeEvent(this->getWindow(), this);
    }
    else if (this->pointer.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                      sf::Mouse::getPosition(*this->getWindow()).y))
    {
        this->currentAction = TypeAction::Hover;
    }
    else  { this->currentAction = TypeAction::Idle; }
}
