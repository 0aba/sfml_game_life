#include "MultilineTextArea.hpp"
#include <cmath>
#include <iostream>


my_gui::MultilineTextArea::MultilineTextArea(sf::RenderWindow& window,
                                             sf::Vector2f size,
                                             sf::Vector2f position,
                                             char *pathFont,
                                             sf::Color textColor,
                                             sf::String text)
{
    this->setWindow(window);
    this->lengthLine = 0;
    this->amountLines = 0;
    this->text = text;
    this->viewText.setCharacterSize(1);

    this->loadFont(pathFont);
    this->setTextColor(textColor);
    this->setText(text);

    ((MultilineTextArea*) this)->setSize(size);
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

void my_gui::MultilineTextArea::setSize(sf::Vector2f size)
{
    short newSize = size.y;
    this->lengthLine = this->text.getSize();
    this->amountLines = 1;

    while (newSize > 1)
    {
        this->lengthLine = std::ceil(size.x / newSize);
        this->amountLines = std::ceil(this->text.getSize() / lengthLine);

        if (newSize * this->lengthLine <= size.x && newSize * this->amountLines  <= size.y)
        {
            this->viewText.setCharacterSize(newSize);
            this->viewText.setString(this->text);
            break;
        }

        --newSize;
    }

    //todo! !!!!!!!!!!!!!!!!!!!!!
    sf::String newViewString;

    for (int i = 0; i < this->text.getSize(); ++i)
    {
        newViewString += this->text[i];
        if (i % this->lengthLine == 0 && i != 0) { newViewString += "\n"; }
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