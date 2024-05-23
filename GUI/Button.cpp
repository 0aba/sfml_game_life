#include "Button.hpp"
#include <cmath>


my_gui::Button::Button(sf::RenderWindow& window,
                       sf::Vector2f size,
                       sf::Vector2f position,
                       char* pathBackgroundTexture,
                       char* pathFont,
                       sf::String text,
                       my_gui::Widget* contextCalled,
                       void (*clickEvent)(Widget* contextCalled, Button* thisButton),
                       sf::Color textColor,
                       sf::Color idleColor,
                       sf::Color hoverColor,
                       sf::Color activeColor)
{
    this->setWindow(window);

    this->text = new my_gui::MultilineTextArea(window,
                                               size,
                                               position,
                                               pathFont,
                                               textColor,
                                               text);

    this->loadBackgroundTexture(pathBackgroundTexture);
    this->backgroundTexture.setSmooth(true);
    this->setClickEvent(clickEvent, contextCalled);
    this->setIdleColor(idleColor);
    this->setHoverColor(hoverColor);
    this->setActiveColor(activeColor);

    // просто this тоже работает, но так нет уведомлений от ide
    ((Button*) this)->setSize(size);
    ((Button*) this)->setPosition(position);
}

my_gui::Button::~Button()
{
    delete this->text;
}

void my_gui::Button::loadFont(char* pathFont) { this->text->loadFont(pathFont); }

void my_gui::Button::setTextColor(sf::Color textColor) { this->text->setTextColor(textColor); }

void my_gui::Button::setText(sf::String text) { this->text->setText(text); }

sf::String my_gui::Button::getText() { return this->text->getText();}

void my_gui::Button::setIdleColor(sf::Color idleColor) { this->idleColor = idleColor; }

void my_gui::Button::setHoverColor(sf::Color hoverColor) { this->hoverColor = hoverColor; }

void my_gui::Button::setActiveColor(sf::Color activeColor) { this->activeColor = activeColor; }

void my_gui::Button::setClickEvent(void (*clickEvent)(Widget* contextCalled, Button* thisButton), my_gui::Widget* contextCalled)
{
    this->contextCalled = contextCalled;
    this->clickEvent = clickEvent;
}

void my_gui::Button::loadBackgroundTexture(char *path)
{
    if(path != nullptr && this->backgroundTexture.loadFromFile(path)) { }
    else if (!this->backgroundTexture.loadFromFile("resources_GUI\\button_background.png")) { return; }

    this->background.setTexture(this->backgroundTexture);
}

void my_gui::Button::setSize(sf::Vector2f size)
{
    this->size = size;
    this->background.setScale(this->getSize().x / this->backgroundTexture.getSize().x,
                              this->getSize().y / this->backgroundTexture.getSize().y);

    this->text->setSize(this->getSize());
}

void my_gui::Button::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->background.setPosition(this->getPosition());
    this->text->setPosition(this->getPosition());
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
    this->text->draw(*this->getWindow());
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
        clickEvent(contextCalled, this);
    }
    else if (this->background.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                         sf::Mouse::getPosition(*this->getWindow()).y))
    {
        this->currentAction = TypeAction::Hover;
    }
    else  { this->currentAction = TypeAction::Idle; }
}


