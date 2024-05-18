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

void my_gui::MultilineTextArea::setSize(sf::Vector2f size)
{
    this->viewText.setString(this->text);
    if (this->text.getSize() == 0) { return; }

    short newSize = 1;
    this->viewText.setCharacterSize(newSize);

    this->amountCharOnLine = this->text.getSize();
    this->amountLines = 1;

    while (newSize < size.y)
    {
        int averageCharWidth = this->viewText.getGlobalBounds().width / this->viewText.getString().getSize();

        this->amountCharOnLine = size.x / averageCharWidth;

        this->amountLines = (this->viewText.getString().getSize() / this->amountCharOnLine) + 1;


        if ((this->viewText.getGlobalBounds().height * this->amountLines * 1.25f) > this->getSize().y )
        {
            --newSize;
            this->viewText.setCharacterSize(newSize);
            averageCharWidth = this->viewText.getGlobalBounds().width / this->viewText.getString().getSize();

            this->amountCharOnLine = size.x / averageCharWidth;

            this->amountLines = (this->viewText.getString().getSize() / this->amountCharOnLine) + 1;
            break;
        }

        ++newSize;
        this->viewText.setCharacterSize(newSize);
    }

    sf::String newViewString;

    for (int i = 0; i < this->text.getSize(); ++i)
    {
        newViewString += this->text[i];
        if  ((i + 1) % this->amountCharOnLine == 0) { newViewString += "\n"; }
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