#include "MultilineTextArea.hpp"
#include <cmath>


my_gui::MultilineTextArea::MultilineTextArea(sf::RenderWindow& window,
                                             sf::Vector2f size,
                                             sf::Vector2f position,
                                             char *pathFont,
                                             sf::Color textColor,
                                             sf::String text)
{
    this->setWindow(window);
    this->text = text;

    this->loadFont(pathFont);
    this->setTextColor(textColor);

    //((MultilineTextArea*) this)->setSize(size);
    this->size = size;
    this->setText(text);
    ((MultilineTextArea*) this)->setPosition(position);
}

void my_gui::MultilineTextArea::loadFont(char *pathFont)
{
    if(pathFont != nullptr && this->font.loadFromFile(pathFont)) { }
    else if (!this->font.loadFromFile("resources_GUI\\arial.ttf")) { return; }

    this->viewText.setFont(this->font);
}

void my_gui::MultilineTextArea::setTextColor(sf::Color textColor)
{
    this->textColor = textColor;

    this->viewText.setFillColor(this->textColor);
}

void my_gui::MultilineTextArea::setText(sf::String text)
{
    this->text = text;

    this->setSize(this->size);
}

sf::String my_gui::MultilineTextArea::getText() { return this->text; }

void my_gui::MultilineTextArea::setSize(sf::Vector2f size) // todo! change
{
    short newSize = 1;
    this->lengthLine = this->text.getSize();
    this->amountLines = 1;

    while (newSize < size.y)
    {
        this->lengthLine = std::ceil(size.x / (newSize * .5f)); // newSize * this->lengthLine <= size.x
        this->amountLines = std::ceil(this->text.getSize() / lengthLine);

        if (newSize > (size.y / this->amountLines))
        {
            break;
        }

        ++newSize;
    }

    this->viewText.setCharacterSize(newSize);

    sf::String newViewString;

    for (int i = 0; i < this->text.getSize(); ++i)
    {
        newViewString += this->text[i];
        if  ((i + 1) % this->lengthLine == 0) { newViewString += "\n"; }
    }

    this->viewText.setString(newViewString);
}

void my_gui::MultilineTextArea::setPosition(sf::Vector2f position)
{
    this->position = position;

    this->viewText.setPosition(this->position);
}

void my_gui::MultilineTextArea::setViewState(bool state) { this->viewState = state; }

void my_gui::MultilineTextArea::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }
    this->setWindow(window);

    this->getWindow()->draw(this->viewText);
}

void my_gui::MultilineTextArea::checkOnEvent(sf::Event event) { /*todo! add events???*/ }