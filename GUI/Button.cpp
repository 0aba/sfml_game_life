#include "Button.hpp"
#include <cmath>


my_gui::Button::Button(sf::RenderWindow& window,
                       sf::Vector2f size,
                       sf::Vector2f position,
                       char* pathBackgroundTexture,
                       char* pathFont,
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
    this->loadFont(pathFont);
    this->setText(text);
    this->setClickEvent(clickEvent);
    this->setTextColor(textColor);
    this->setIdleColor(idleColor);
    this->setHoverColor(hoverColor);
    this->setActiveColor(activeColor);

    // просто this тоже работает, но так нет уведомлений от ide
    ((Button*) this)->setSize(size);
    ((Button*) this)->setPosition(position);
}

void my_gui::Button::loadFont(const char* pathFont)
{
    this->font.loadFromFile(pathFont);
    this->text.setFont(this->font);
}

void my_gui::Button::setTextColor(sf::Color textColor)
{
    this->textColor = textColor;
    this->text.setFillColor(this->textColor);
}

void my_gui::Button::setText(sf::String text)
{
    this->text.setString(text);
    
    this->setPosition(this->getPosition());
}

sf::String my_gui::Button::getText() { return this->text.getString();}

void my_gui::Button::setIdleColor(sf::Color idleColor) { this->idleColor = idleColor; }

void my_gui::Button::setHoverColor(sf::Color hoverColor) { this->hoverColor = hoverColor; }

void my_gui::Button::setActiveColor(sf::Color activeColor) { this->activeColor = activeColor; }

void my_gui::Button::setClickEvent(void (*clickEvent)(sf::RenderWindow* window, Widget* widget)) { this->clickEvent = clickEvent; }

void my_gui::Button::loadBackgroundTexture(const char *path)
{
    if(!this->backgroundTexture.loadFromFile(path)) { return; }

    background.setTexture(this->backgroundTexture);
}

void my_gui::Button::setSize(sf::Vector2f size)
{
    this->size = size;
    this->background.setScale( this->getSize().x / this->backgroundTexture.getSize().x,
                               this->getSize().y / this->backgroundTexture.getSize().y);

    this->text.setCharacterSize(std::ceil(this->backgroundTexture.getSize().y * this->background.getScale().y * .5f));
    this->setPosition(this->getPosition());
}

void my_gui::Button::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->background.setPosition(this->getPosition());
    this->text.setPosition(this->background.getPosition().x +
                           this->getSize().x * .5f -
                           (this->text.getString().getSize() * this->text.getCharacterSize() * .25f),
                           this->background.getPosition().y +
                           this->getSize().y * .5f -
                           this->text.getCharacterSize() * .5f);
}

void my_gui::Button::setViewState(bool state) { this->viewState = state; }

void my_gui::Button::draw(sf::RenderWindow& window)
{
    if(!this->getViewState()) { return; }

    this->setWindow(window);

    if (this->currentAction == TypeAction::Activated) { this->background.setColor(this->activeColor); }
    else if (this->currentAction == TypeAction::Hover) { this->background.setColor(this->hoverColor); }
    else /*(this->currentAction == TypeAction::Idle)*/ { this->background.setColor(this->idleColor); }

    this->getWindow()->draw(this->background);
    this->getWindow()->draw(this->text);
}

void my_gui::Button::checkOnEvent(sf::Event event)
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
