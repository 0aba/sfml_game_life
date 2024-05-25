#include "Page.hpp"


Page::Page(sf::RenderWindow* window, TypePage* pageView)
{
    this->setWindow(window);
    this->pageView = pageView;
}

void Page::setWindow(sf::RenderWindow *window) { this->window = window; }

sf::RenderWindow* Page::getWindow() { return this->window; }

