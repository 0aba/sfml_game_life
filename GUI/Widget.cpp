#include "Widget.hpp"


void my_gui::Widget::setWindow(sf::RenderWindow& window) {  this->window = &window; }
sf::RenderWindow* my_gui::Widget::getWindow() { return this->window; }

sf::Vector2f my_gui::Widget::getSize() { return this->size; }

sf::Vector2f my_gui::Widget::getPosition() { return this->position; }
bool my_gui::Widget::getViewState() const { return this->viewState; }