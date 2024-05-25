#include "SettingsPage.hpp"


SettingsPage::SettingsPage(sf::RenderWindow* window, TypePage* pageView, Game* game) : Page(window, pageView)
{
    this->game = game;

    if (!this->font.loadFromFile(".\\resources_GUI\\arial.ttf")) { return; }

    this->titleAlive.setFont(this->font);
    this->titleAlive.setCharacterSize(15);
    this->titleAlive.setString("Alive Percent");
    this->titleAlive.setPosition(sf::Vector2f (20, 20));
    this->sliderAlivePercent = new my_gui::HSlider(*this->getWindow(),
                                                   sf::Vector2f (400, 25),
                                                   sf::Vector2f (20, 70),
                                                   nullptr,
                                                   nullptr,
                                                   nullptr,
                                                   nullptr,
                                                   .5f,
                                                   this,
                                                   SettingsPage::changeAlivePercent,
                                                   sf::Color(50, 50, 50),
                                                   sf::Color(100, 100, 100),
                                                   sf::Color(150, 150, 150),
                                                   sf::Color(200, 200, 200),
                                                   Game::MIN_VALUE_LIVING,
                                                   Game::MAX_VALUE_LIVING
    );
    this->titleWall.setFont(this->font);
    this->titleWall.setCharacterSize(15);
    this->titleWall.setString("Wall Percent");
    this->titleWall.setPosition(sf::Vector2f (20, 110));
    this->sliderWallPercent = new my_gui::HSlider(*this->getWindow(),
                                                  sf::Vector2f (400, 25),
                                                  sf::Vector2f (20, 160),
                                                  nullptr,
                                                  nullptr,
                                                  nullptr,
                                                  nullptr,
                                                  .5f,
                                                  this,
                                                  SettingsPage::changeWallPercent,
                                                  sf::Color(50, 50, 50),
                                                  sf::Color(100, 100, 100),
                                                  sf::Color(150, 150, 150),
                                                  sf::Color(200, 200, 200),
                                                  Game::MIN_VALUE_SPECIAL_CELL,
                                                  Game::MAX_VALUE_SPECIAL_CELL
    );
    this->titleSupport.setFont(this->font);
    this->titleSupport.setCharacterSize(15);
    this->titleSupport.setString("Support Percent");
    this->titleSupport.setPosition(sf::Vector2f (20, 200));
    this->sliderSupportPercent = new my_gui::HSlider(*this->getWindow(),
                                                     sf::Vector2f (400, 25),
                                                     sf::Vector2f (20, 250),
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     .5f,
                                                     this,
                                                     SettingsPage::changeSupportPercent,
                                                     sf::Color(50, 50, 50),
                                                     sf::Color(100, 100, 100),
                                                     sf::Color(150, 150, 150),
                                                     sf::Color(200, 200, 200),
                                                     Game::MIN_VALUE_SPECIAL_CELL,
                                                     Game::MAX_VALUE_SPECIAL_CELL
    );
    this->titleKilling.setFont(this->font);
    this->titleKilling.setCharacterSize(15);
    this->titleKilling.setString("Support Killing");
    this->titleKilling.setPosition(sf::Vector2f (20, 290));
    this->sliderKillingPercent = new my_gui::HSlider(*this->getWindow(),
                                                     sf::Vector2f (400, 25),
                                                     sf::Vector2f (20, 340),
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     .5f,
                                                     this,
                                                     SettingsPage::changeKillingPercent,
                                                     sf::Color(50, 50, 50),
                                                     sf::Color(100, 100, 100),
                                                     sf::Color(150, 150, 150),
                                                     sf::Color(200, 200, 200),
                                                     Game::MIN_VALUE_SPECIAL_CELL,
                                                     Game::MAX_VALUE_SPECIAL_CELL
    );

    this->backButton = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (200, 50),
                                          sf::Vector2f (20, 525),
                                          nullptr,
                                          nullptr,
                                          "back to menu",
                                          this,
                                          [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((SettingsPage*) contextCalled)->pageView = TypePage::MenuPageType; },
                                          sf::Color(150, 150, 150),
                                          sf::Color(10, 25, 75),
                                          sf::Color(15, 50, 150),
                                          sf::Color(30, 100, 250)
                                          );
}


void SettingsPage::drawOnWindow(sf::RenderWindow& window)
{
    this->getWindow()->draw(this->titleAlive);
    this->sliderAlivePercent->draw(*this->getWindow());
    this->getWindow()->draw(this->titleWall);
    this->sliderWallPercent->draw(*this->getWindow());
    this->getWindow()->draw(this->titleSupport);
    this->sliderSupportPercent->draw(*this->getWindow());
    this->getWindow()->draw(this->titleKilling);
    this->sliderKillingPercent->draw(*this->getWindow());

    this->backButton->draw(window);
}

void SettingsPage::checkOnEvent(sf::Event& event)
{
    this->sliderAlivePercent->checkOnEvent(event);
    this->sliderWallPercent->checkOnEvent(event);
    this->sliderSupportPercent->checkOnEvent(event);
    this->sliderKillingPercent->checkOnEvent(event);

    this->backButton->checkOnEvent(event);
}

SettingsPage::~SettingsPage()
{
    this->sliderAlivePercent;
    this->sliderWallPercent;
    this->sliderSupportPercent;
    this->sliderKillingPercent;
}

void SettingsPage::changeAlivePercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->game->setLivingPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeWallPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->game->setWallPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeSupportPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->game->setSupportPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeKillingPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->game->setKillingPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

