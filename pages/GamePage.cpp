#include "GamePage.hpp"


GamePage::GamePage(sf::RenderWindow* window, TypePage* pageView, Game* game) : Page(window, pageView)
{
    this->backButton = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (200, 50),
                                          sf::Vector2f (50, 525),
                                          nullptr,
                                          nullptr,
                                          "back to menu",
                                          this,
                                          [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)
                                          {
                                              ((GamePage*) contextCalled)->gameWidget->breakGame();
                                              *((GamePage*) contextCalled)->pageView = TypePage::MenuPageType;
                                          },
                                          sf::Color(150, 150, 150),
                                          sf::Color(10, 25, 75),
                                          sf::Color(15, 50, 150),
                                          sf::Color(30, 100, 250)
                                      );

    this->gameWidget = new GameWidget (this->getWindow(),
                                       sf::Vector2f (700, 500),
                                       sf::Vector2f (10, 10),
                                       game,
                                       Game::DEFAULT_SIDE_SIZE,
                                       Game::DEFAULT_SIDE_SIZE);

}


void GamePage::drawOnWindow(sf::RenderWindow& window)
{
    this->gameWidget->draw(*this->getWindow());
    this->backButton->draw(*this->getWindow());
}

void GamePage::checkOnEvent(sf::Event& event)
{
    this->gameWidget->checkOnEvent(event);
    this->backButton->checkOnEvent(event);
}

GamePage::~GamePage()
{
    delete this->gameWidget;
    delete this->backButton;
}
