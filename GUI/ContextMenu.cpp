#include "ContextMenu.hpp"


my_gui::ContextMenu::ContextMenu(sf::RenderWindow &window,
                                 sf::Vector2f size,
                                 sf::Vector2f position,
                                 char* pathBackgroundTexture)
{
    this->setWindow(window);
    this->lastElement = std::distance(this->elements.begin(), this->elements.end());

    this->loadBackgroundTexture(pathBackgroundTexture);

    ((ContextMenu*)this)->setSize(size);
    ((ContextMenu*)this)->setPosition(position);
}

void my_gui::ContextMenu::loadBackgroundTexture(char *path)
{
    if(path != nullptr && this->backgroundTexture.loadFromFile(path)) { }
    else if (!this->backgroundTexture.loadFromFile("resources_GUI\\context_menu.png")) { return; }

    background.setTexture(this->backgroundTexture);
}

unsigned short my_gui::ContextMenu::createElement()
{
    this->elements.push_front( new ContextMenuElement (*this->getWindow(),
                                          this->elementSize,
                                          sf::Vector2f(0, 0),
                                          nullptr,
                                          nullptr,
                                          nullptr,
                                          "default",
                                          this,
                                          *([](my_gui::Widget* contextCalled, ContextMenuElement* thisElement) { }),
                                          sf::Color(255, 219, 200),
                                          sf::Color(110, 110, 110, 105),
                                          sf::Color(151, 197, 139, 64),
                                          sf::Color(98, 97, 160, 128)
                                          ));
    this->lastElement = std::distance(this->elements.begin(), this->elements.end());

    this->setSize(this->size);
    this->setPosition(this->position);

    return lastElement;
}

unsigned short my_gui::ContextMenu::createElement(char *pathBackgroundTexture,
                                                 char *pathImage,
                                                 char *pathFont,
                                                 sf::String text,
                                                 my_gui::Widget* contextCalled,
                                                 void (*clickEvent)(my_gui::Widget* contextCalled, ContextMenuElement* thisElement),
                                                 sf::Color textColor,
                                                 sf::Color idleColor,
                                                 sf::Color hoverColor,
                                                 sf::Color activeColor)
{
    this->elements.push_front( new ContextMenuElement (*this->getWindow(),
                                                       this->elementSize,
                                                       sf::Vector2f(0, 0),
                                                       pathBackgroundTexture,
                                                       pathImage,
                                                       pathFont,
                                                       text,
                                                       contextCalled,
                                                       clickEvent,
                                                       textColor,
                                                       idleColor,
                                                       hoverColor,
                                                       activeColor
    ));
    this->lastElement = std::distance(this->elements.begin(), this->elements.end());

    this->setSize(this->size);
    this->setPosition(this->position);

    return lastElement;
}

my_gui::ContextMenuElement* my_gui::ContextMenu::getElementAt(unsigned short index)
{
    auto iterator = this->elements.begin();
    std::advance(iterator, index);

    return *iterator;
}

void my_gui::ContextMenu::delElementAt(unsigned short index)
{
    auto iterator = this->elements.begin();
    std::advance(iterator, index);

    delete *iterator;
    this->elements.erase(iterator);

    this->lastElement = std::distance(this->elements.begin(), this->elements.end());

    this->setSize(this->size);
    this->setPosition(this->position);
}

unsigned short my_gui::ContextMenu::getIndexLastElement() const { return this->lastElement; }

void my_gui::ContextMenu::setSize(sf::Vector2f size)
{
    this->size = size;

    this->background.setScale(this->getSize().x / this->backgroundTexture.getSize().x,
                              this->getSize().y / this->backgroundTexture.getSize().y);
    this->elementSize = sf::Vector2f (this->getSize().x,
                                      this->getSize().y / (this->lastElement == 0 ? 1: this->lastElement));

    for (auto i = this->elements.begin(); i != this->elements.end(); ++i) { (*i)->setSize(this->elementSize); }
}

void my_gui::ContextMenu::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->background.setPosition(this->getPosition());

    int step = 0;
    for (auto i = this->elements.begin(); i != this->elements.end(); ++i, ++step)
    {
        (*i)->setPosition(sf::Vector2f (this->getPosition().x,
                                        this->getPosition().y +
                                        this->elementSize.y * step));
    }

}

void my_gui::ContextMenu::setViewState(bool state) { this->viewState = state; }

void my_gui::ContextMenu::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    this->getWindow()->draw(this->background);

    for (auto i = this->elements.begin(); i != this->elements.end(); ++i) { (*i)->draw(*this->getWindow()); }
}

void my_gui::ContextMenu::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    for (auto i = this->elements.begin(); i != this->elements.end(); ++i) { (*i)->checkOnEvent(event); }
}

my_gui::ContextMenu::~ContextMenu()
{
    for (auto i = this->elements.begin(); i != this->elements.end(); ++i) { delete *i; }
}