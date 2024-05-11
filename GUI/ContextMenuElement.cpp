#include "ContextMenuElement.hpp"
#include <cmath>


my_gui::ContextMenuElement::ContextMenuElement(sf::RenderWindow &window,
                                               sf::Vector2f size,
                                               sf::Vector2f position,
                                               char *pathBackgroundTexture,
                                               char *pathImage,
                                               char *pathFont,
                                               sf::String text,
                                               void (*clickEvent)(sf::RenderWindow* window, Widget* widget),
                                               sf::Color textColor,
                                               sf::Color idleColor,
                                               sf::Color hoverColor,
                                               sf::Color activeColor)
{
    this->setWindow(window);

    this->loadBackgroundTexture(pathBackgroundTexture);
    this->backgroundTexture.setSmooth(true);
    this->loadImage(pathImage);
    this->imageTexture.setSmooth(true);
    this->loadFont(pathFont);
    this->setText(text);
    this->setClickEvent(clickEvent);
    this->setTextColor(textColor);
    this->setIdleColor(idleColor);
    this->setHoverColor(hoverColor);
    this->setActiveColor(activeColor);

    // просто this тоже работает, но так нет уведомлений от ide
    ((ContextMenuElement*) this)->setSize(size);
    ((ContextMenuElement*) this)->setPosition(position);
}

void my_gui::ContextMenuElement::loadBackgroundTexture(char *path)
{
    if(!this->backgroundTexture.loadFromFile(path)) { return; }

    background.setTexture(this->backgroundTexture);
}

void my_gui::ContextMenuElement::loadImage(char *path)
{
    if(!this->imageTexture.loadFromFile(path)) { return; }

    this->image.setTexture(imageTexture);
}

void my_gui::ContextMenuElement::loadFont(const char *pathFont)
{
    if(!this->font.loadFromFile(pathFont)) { return; }

    this->text.setFont(this->font);
}

void my_gui::ContextMenuElement::setTextColor(sf::Color textColor)
{
    this->textColor = textColor;

    text.setFillColor(this->textColor);
}

void my_gui::ContextMenuElement::setText(sf::String text) { this->text.setString(text); }

sf::String my_gui::ContextMenuElement::getText() {return this->text.getString(); }

void my_gui::ContextMenuElement::setClickEvent(void (*clickEvent)(sf::RenderWindow *, Widget *)) { this->clickEvent = clickEvent; }

void my_gui::ContextMenuElement::setIdleColor(sf::Color idleColor) { this->idleColor = idleColor; }

void my_gui::ContextMenuElement::setHoverColor(sf::Color hoverColor) { this->hoverColor = hoverColor; }

void my_gui::ContextMenuElement::setActiveColor(sf::Color activeColor) { this->activeColor = activeColor; }

void my_gui::ContextMenuElement::setSize(sf::Vector2f size)
{
    this->size = size;
    this->background.setScale( this->getSize().x / this->backgroundTexture.getSize().x,
                               this->getSize().y / this->backgroundTexture.getSize().y);

    this->image.setScale( this->getSize().x * .2f / this->imageTexture.getSize().x,
                          this->getSize().y / this->imageTexture.getSize().y);

    this->text.setCharacterSize(std::ceil(this->backgroundTexture.getSize().y * this->background.getScale().y * .5f));
}

void my_gui::ContextMenuElement::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->background.setPosition(this->position);

    this->image.setPosition(this->position);

    this->text.setPosition(this->background.getPosition().x +
                           this->getSize().x * .5f -
                           (this->text.getString().getSize() * this->text.getCharacterSize() * .25f) +
                           this->backgroundTexture.getSize().x * this->background.getScale().x * .21f,
                           this->background.getPosition().y +
                           this->getSize().y * .5f -
                           this->text.getCharacterSize() * .5f
                           );
}

void my_gui::ContextMenuElement::setViewState(bool state) { this->viewState = state; }

void my_gui::ContextMenuElement::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    this->setWindow(window);

    if (this->currentAction == TypeAction::Activated) { this->background.setColor(this->activeColor); }
    else if (this->currentAction == TypeAction::Hover) { this->background.setColor(this->hoverColor); }
    else /*(this->currentAction == TypeAction::Idle)*/ { this->background.setColor(this->idleColor); }

    this->getWindow()->draw(this->background);
    this->getWindow()->draw(this->image);
    this->getWindow()->draw(this->text);
}

void my_gui::ContextMenuElement::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    if (event.type == sf::Event::MouseButtonPressed
        &&
        this->background.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                    sf::Mouse::getPosition(*this->getWindow()).y))
    {
        this->currentAction = TypeAction::Activated;
        clickEvent(this->getWindow(), this);
    }
    else if (this->background.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                         sf::Mouse::getPosition(*this->getWindow()).y))
    {
        this->currentAction = TypeAction::Hover;
    }
    else  { this->currentAction = TypeAction::Idle; }
}

