#include "SettingsPage.hpp"


SettingsPage::SettingsPage(sf::RenderWindow* window, TypePage* pageView, Game* game) : Page(window, pageView)
{
    this->backButton = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (200, 50),
                                          sf::Vector2f (50, 525),
                                          nullptr,
                                          nullptr,
                                          "back to menu",
                                          this,
                                          [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((SettingsPage*) contextCalled)->pageView = TypePage::MenuPageType;  },
                                          sf::Color(150, 150, 150),
                                          sf::Color(10, 25, 75),
                                          sf::Color(15, 50, 150),
                                          sf::Color(30, 100, 250)
                                          );
}


void SettingsPage::drawOnWindow(sf::RenderWindow& window)
{
    this->backButton->draw(window);
}

void SettingsPage::checkOnEvent(sf::Event& event)
{
    this->backButton->checkOnEvent(event);
}

SettingsPage::~SettingsPage()
{

}
