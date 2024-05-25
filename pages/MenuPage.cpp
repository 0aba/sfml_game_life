#include "MenuPage.hpp"
#include "Utils.hpp"



MenuPage::MenuPage(sf::RenderWindow* window, TypePage* pageView) : Page(window, pageView)
{
    this->pageView = pageView;


    this->textPlay = new my_gui::Button(*this->getWindow(),
                                        sf::Vector2f (100, 50),
                                        sf::Vector2f (300, 100),
                                        nullptr,
                                        nullptr,
                                        "Play",
                                        this,
                                        [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((MenuPage*) contextCalled)->pageView = TypePage::GamePageType; },
                                        sf::Color(150, 150, 150),
                                        sf::Color(10, 25, 75),
                                        sf::Color(15, 50, 150),
                                        sf::Color(30, 100, 250)
                                        );
    this->textSettings = new my_gui::Button(*this->getWindow(),
                                            sf::Vector2f (100, 50),
                                            sf::Vector2f (300, 200),
                                            nullptr,
                                            nullptr,
                                            "Settings",
                                            this,
                                            [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((MenuPage*) contextCalled)->pageView = TypePage::SettingsPageType; },
                                            sf::Color(150, 150, 150),
                                            sf::Color(10, 25, 75),
                                            sf::Color(15, 50, 150),
                                            sf::Color(30, 100, 250)
                                            );
    this->textRules = new my_gui::Button(*this->getWindow(),
                                         sf::Vector2f (100, 50),
                                         sf::Vector2f (300, 300),
                                         nullptr,
                                         nullptr,
                                         "Rules",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((MenuPage*) contextCalled)->pageView = TypePage::RulesPageType; },
                                         sf::Color(150, 150, 150),
                                         sf::Color(10, 25, 75),
                                         sf::Color(15, 50, 150),
                                         sf::Color(30, 100, 250)
                                         );
    this->textExit =  new my_gui::Button(*this->getWindow(),
                                         sf::Vector2f (100, 50),
                                         sf::Vector2f (300, 400),
                                         nullptr,
                                         nullptr,
                                         "Exit",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((MenuPage*) contextCalled)->pageView = TypePage::ExitPageType; },
                                         sf::Color(150, 150, 150),
                                         sf::Color(10, 25, 75),
                                         sf::Color(15, 50, 150),
                                         sf::Color(30, 100, 250)
                                         );
}

void MenuPage::drawOnWindow(sf::RenderWindow& window)
{
    this->textPlay->draw(window);
    this->textSettings->draw(window);
    this->textRules->draw(window);
    this->textExit->draw(window);
}

MenuPage::~MenuPage()
{
    delete this->textPlay;
    delete this->textSettings;
    delete this->textRules;
    delete this->textExit;
}

void MenuPage::checkOnEvent(sf::Event& event)
{
    this->textPlay->checkOnEvent(event);
    this->textSettings->checkOnEvent(event);
    this->textRules->checkOnEvent(event);
    this->textExit->checkOnEvent(event);
}

