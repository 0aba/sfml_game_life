#include "SettingsPage.hpp"


SettingsPage::SettingsPage(sf::RenderWindow* window, TypePage* pageView, GameWidget* gameWidget) : Page(window, pageView)
{
    this->gameWidget = gameWidget;

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

    this->titleAmountX.setFont(this->font);
    this->titleAmountX.setCharacterSize(15);
    this->titleAmountX.setString("Amount x");
    this->titleAmountX.setPosition(sf::Vector2f (20, 380));
    this->sliderAmountX = new my_gui::HSlider(*this->getWindow(),
                                                     sf::Vector2f (400, 25),
                                                     sf::Vector2f (20, 430),
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     .5f,
                                                     this,
                                                     SettingsPage::changeAmountX,
                                                     sf::Color(50, 50, 50),
                                                     sf::Color(100, 100, 100),
                                                     sf::Color(150, 150, 150),
                                                     sf::Color(200, 200, 200),
                                                     GameWidget::MIN_SIZE_SIDE,
                                                     GameWidget::MAX_SIZE_SIDE
    );

    this->titleAmountY.setFont(this->font);
    this->titleAmountY.setCharacterSize(15);
    this->titleAmountY.setString("Amount y");
    this->titleAmountY.setPosition(sf::Vector2f (20, 470));
    this->sliderAmountY = new my_gui::HSlider(*this->getWindow(),
                                                     sf::Vector2f (400, 25),
                                                     sf::Vector2f (20, 520),
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     nullptr,
                                                     .5f,
                                                     this,
                                                     SettingsPage::changeAmountY,
                                                     sf::Color(50, 50, 50),
                                                     sf::Color(100, 100, 100),
                                                     sf::Color(150, 150, 150),
                                                     sf::Color(200, 200, 200),
                                                     GameWidget::MIN_SIZE_SIDE,
                                                     GameWidget::MAX_SIZE_SIDE
    );

    this->backButton = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (200, 50),
                                          sf::Vector2f (20, 600),
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
    this->getWindow()->draw(this->titleAmountX);
    this->sliderAmountX->draw(*this->getWindow());
    this->getWindow()->draw(this->titleAmountY);
    this->sliderAmountY->draw(*this->getWindow());

    this->backButton->draw(window);
}

void SettingsPage::checkOnEvent(sf::Event& event)
{
    this->sliderAlivePercent->checkOnEvent(event);
    this->sliderWallPercent->checkOnEvent(event);
    this->sliderSupportPercent->checkOnEvent(event);
    this->sliderKillingPercent->checkOnEvent(event);
    this->sliderAmountX->checkOnEvent(event);
    this->sliderAmountY->checkOnEvent(event);

    this->backButton->checkOnEvent(event);
}

SettingsPage::~SettingsPage()
{
    delete this->sliderAlivePercent;
    delete this->sliderWallPercent;
    delete this->sliderSupportPercent;
    delete this->sliderKillingPercent;
    delete this->sliderAmountX;
    delete this->sliderAmountY;
}

void SettingsPage::changeAlivePercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setLivingPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeWallPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setWallPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeSupportPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setSupportPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeKillingPercent(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setKillingPercent(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeAmountX(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setAmountCellOnX(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

void SettingsPage::changeAmountY(my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider)
{
    ((SettingsPage*) contextCalled)->gameWidget->setAmountCellOnY(((my_gui::HSlider*) thisSlider)->getValuesPointer());
}

