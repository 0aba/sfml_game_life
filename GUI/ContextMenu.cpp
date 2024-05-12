#include "ContextMenu.hpp"


my_gui::ContextMenu::ContextMenu(sf::RenderWindow &window,
                                 sf::Vector2f size,
                                 sf::Vector2f position,
                                 char* pathBackgroundTexture,
                                 unsigned short maxAmountElements)
{
    this->setWindow(window);
    this->setMaxAmountElements(maxAmountElements);
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

void my_gui::ContextMenu::setMaxAmountElements(unsigned short amount)
{
    if (elements != nullptr && this->maxAmountElements == amount) { return; }
    else if (elements == nullptr)
    {
        this->maxAmountElements = amount;
        this->elements = new ContextMenuElement*[maxAmountElements];
    }
    else /*(elements != nullptr && this->maxAmountElements != amount)*/
    {
        ContextMenuElement** newElementsArray = new my_gui::ContextMenuElement*[amount];

        for (int i = 0; i < amount && i < this->maxAmountElements; ++i) { newElementsArray[i] = elements[i]; }

        delete[] this->elements;
        if (amount < this->lastElement) { this->lastElement = amount - 1; }

        this->maxAmountElements = amount;
        this->elements = newElementsArray;

        this->setSize(this->size);
        this->setPosition(this->position);
    }
}

unsigned short my_gui::ContextMenu::getMaxAmountElements() const { return this->maxAmountElements; }

unsigned short my_gui::ContextMenu::addElement(my_gui::ContextMenuElement* element)
{
    if (this->lastElement == MAX_AMOUNT_ELEMENTS) { return NOT_FOUND_ELEMENT; }

    this->elements[++this->lastElement] = element;

    this->setSize(this->size);
    this->setPosition(this->position);
    return this->lastElement;
}

unsigned short my_gui::ContextMenu::createDefaultElement()
{
    if (this->lastElement == MAX_AMOUNT_ELEMENTS) { return NOT_FOUND_ELEMENT; }

    this->elements[++this->lastElement] = new ContextMenuElement (*this->getWindow(),
                                          this->elementSize,
                                          sf::Vector2f(300, 50),
                                          nullptr,
                                          nullptr,
                                          nullptr,
                                          "default",
                                          *([](sf::RenderWindow* window, my_gui::Widget* widget) { }),
                                          sf::Color(255, 219, 200),
                                          sf::Color(110, 110, 110, 105),
                                          sf::Color(151, 197, 139, 64),
                                          sf::Color(98, 97, 160, 128)
                                          );

    this->setSize(this->size);
    this->setPosition(this->position);
    return this->lastElement;
}

my_gui::ContextMenuElement* my_gui::ContextMenu::getElementAt(unsigned short index)
{
    return  (index <= this->lastElement) ? this->elements[index]: nullptr;
}

void my_gui::ContextMenu::delElementAt(unsigned short index)
{
    if (index > this->lastElement) { return; }

    this->elements[index] = nullptr;

    for (int i = index; i < this->lastElement; ++i) { this->elements[i] = this->elements[i + 1]; }

    --this->lastElement;

    this->setSize(this->size);
    this->setPosition(this->position);
}

void my_gui::ContextMenu::freeMemoryWidget()
{
    for (int i = 0; i <= this->lastElement; ++i) { delete this->elements[i]; }

    delete[] this->elements;
}

void my_gui::ContextMenu::setSize(sf::Vector2f size)
{
    this->size = size;

    this->background.setScale(this->getSize().x / this->backgroundTexture.getSize().x,
                              this->getSize().y / this->backgroundTexture.getSize().y);
    this->elementSize = sf::Vector2f (this->getSize().x,
                                      this->getSize().y / ((this->lastElement == -1 ? 0: this->lastElement) + 1));

    for (int i = 0; i <= this->lastElement; ++i) { this->elements[i]->setSize(this->elementSize); }
}

void my_gui::ContextMenu::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->background.setPosition(this->getPosition());

    for (int i = 0; i <= this->lastElement; ++i)
    {
        this->elements[i]->setPosition(sf::Vector2f (this->getPosition().x,
                                                     this->getPosition().y +
                                                     this->elements[i]->getSize().y * i));
    }
}

void my_gui::ContextMenu::setViewState(bool state) { this->viewState = state; }

void my_gui::ContextMenu::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    this->getWindow()->draw(this->background);

    for (int i = 0; i <= this->lastElement; ++i) { this->getElementAt(i)->draw(window); }
}

void my_gui::ContextMenu::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    for (int i = 0; i <= this->lastElement; ++i) { this->getElementAt(i)->checkOnEvent(event); }
}