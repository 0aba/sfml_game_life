#include "Cell.hpp"


Cell::Cell(sf::Vector2f size,
           sf::Vector2f position,
           char *pathCellTexture)
{
    this->loadCellTexture(pathCellTexture);

    ((Cell*) this)->setSize(size);
    ((Cell*) this)->setPosition(position);
}

void Cell::loadCellTexture(char *path)
{
    if(path != nullptr && this->cellTexture.loadFromFile(path)) { }
    else if (!this->cellTexture.loadFromFile("resources_GUI\\button_background.png")) { return; }

    this->cellSprite.setTexture(this->cellTexture);
}

void Cell::setSize(sf::Vector2f size)
{
    this->cellSprite.setScale(this->getSize().x / this->cellTexture.getSize().x,
                              this->getSize().y / this->cellTexture.getSize().y);
}

void Cell::setPosition(sf::Vector2f position) { this->cellSprite.setPosition(position); }

void Cell::setViewState(bool state) { this->viewState = state; }

void Cell::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    this->setWindow(window);

    this->getWindow()->draw(this->cellSprite);
}

void Cell::checkOnEvent(sf::Event event) {/* todo! ??*/}
