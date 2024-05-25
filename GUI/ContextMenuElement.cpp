#include "ContextMenuElement.hpp"
#include <cmath>


my_gui::ContextMenuElement::ContextMenuElement(sf::RenderWindow &window,
                                               sf::Vector2f size,
                                               sf::Vector2f position,
                                               char *pathBackgroundTexture,
                                               char *pathImage,
                                               char *pathFont,
                                               sf::String text,
                                               OBJECT_GUI* contextCalled,
                                               void (*clickEvent)(OBJECT_GUI* contextCalled, ContextMenuElement* thisElement),
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
    this->loadImage(pathImage);
    this->imageTexture.setSmooth(true);
    this->setClickEvent(clickEvent, contextCalled);
    this->setIdleColor(idleColor);
    this->setHoverColor(hoverColor);
    this->setActiveColor(activeColor);

    // просто this тоже работает, но так нет уведомлений от ide
    ((ContextMenuElement*) this)->setSize(size);
    ((ContextMenuElement*) this)->setPosition(position);
}

my_gui::ContextMenuElement::~ContextMenuElement()
{
    delete this->text;
}

void my_gui::ContextMenuElement::loadBackgroundTexture(char *path)
{
    if(path != nullptr && this->backgroundTexture.loadFromFile(path)) { }
    else if (!this->backgroundTexture.loadFromFile("resources_GUI\\context_menu_element.png")) { return; }

    background.setTexture(this->backgroundTexture);
}

void my_gui::ContextMenuElement::loadImage(char *path)
{
    if(path != nullptr && this->imageTexture.loadFromFile(path)) { }
    else if (!this->imageTexture.loadFromFile("resources_GUI\\none_image.png")) { return; }

    this->image.setTexture(imageTexture);
}

void my_gui::ContextMenuElement::loadFont(const char *pathFont) { this->text->loadFont(pathFont); }

void my_gui::ContextMenuElement::setTextColor(sf::Color textColor) {}

void my_gui::ContextMenuElement::setText(sf::String text) { this->text->setText(text); }

sf::String my_gui::ContextMenuElement::getText() {return this->text->getText(); }

void my_gui::ContextMenuElement::setClickEvent(void (*clickEvent)(OBJECT_GUI* contextCalled, ContextMenuElement* thisElement), OBJECT_GUI* contextCalled)
{
    this->contextCalled = contextCalled;
    this->clickEvent = clickEvent;
}

void my_gui::ContextMenuElement::setIdleColor(sf::Color idleColor) { this->idleColor = idleColor; }

void my_gui::ContextMenuElement::setHoverColor(sf::Color hoverColor) { this->hoverColor = hoverColor; }

void my_gui::ContextMenuElement::setActiveColor(sf::Color activeColor) { this->activeColor = activeColor; }

void my_gui::ContextMenuElement::setSize(sf::Vector2f size)
{
    this->size = size;
    this->background.setScale(this->getSize().x / this->backgroundTexture.getSize().x,
                              this->getSize().y / this->backgroundTexture.getSize().y);

    //todo! поправить scale пропорции для картинок
    this->image.setScale( this->getSize().x * .2f / this->imageTexture.getSize().x,
                          this->getSize().y / this->imageTexture.getSize().y);

    this->text->setSize(sf::Vector2f (this->getSize().x * .66f, this->getSize().y));
}

void my_gui::ContextMenuElement::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->background.setPosition(this->position);

    this->image.setPosition(sf::Vector2f (this->getPosition().x +
                                          this->getSize().x * .02f,
                                          this->getPosition().y));

    this->text->setPosition(sf::Vector2f (this->getPosition().x +
                                          this->getSize().x * .3f,
                                          this->getPosition().y));
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
    this->text->draw(*this->getWindow());
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

        clickEvent(contextCalled, this);
    }
    else if (this->background.getGlobalBounds().contains(sf::Mouse::getPosition(*this->getWindow()).x,
                                                         sf::Mouse::getPosition(*this->getWindow()).y))
    {
        this->currentAction = TypeAction::Hover;
    }
    else  { this->currentAction = TypeAction::Idle; }
}

