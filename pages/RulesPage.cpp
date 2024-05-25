#include "RulesPage.hpp"


RulesPage::RulesPage(sf::RenderWindow* window, TypePage* pageView) : Page(window, pageView)
{
    if (!font.loadFromFile(".\\resources_GUI\\arial.ttf")) { return; }

    textRules.setFont(font);
    textRules.setString("Type cell:\n \
                       '#' - living cell.\n\
                       '_' - dead cell.\n\
                       'W' - wall, occupies a cell and does not interact \n\
                        with other cells.\n\
                       'K' - Killing cell, kills neighbors if they are alive.\n\
                       Has a higher priority than the life support cell.\n\
                       'S' - Life support cell, supports the life of cells,\n\
                       even if condition (rule 1) is not met.\n\
\
                       RulesPageType:\n\
                       ~ If a dead cell is surrounded by exactly 3 living ones,\n\
                         then it becomes alive.\n\
                       ~ If a living cell is surrounded by 2 or 3 living ones, \n\
                         then it remains alive, otherwise it is either\n\
                         from loneliness or from overcrowding."
                       );

    textRules.setCharacterSize(24);
    textRules.setFillColor(sf::Color(119, 136, 153));
    textRules.setPosition(10, 10);

    this->backButton = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (200, 50),
                                          sf::Vector2f (50, 525),
                                          nullptr,
                                          nullptr,
                                          "back to menu",
                                          this,
                                          [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)  { *((RulesPage*) contextCalled)->pageView = TypePage::MenuPageType;  },
                                          sf::Color(150, 150, 150),
                                          sf::Color(10, 25, 75),
                                          sf::Color(15, 50, 150),
                                          sf::Color(30, 100, 250)
    );
}

void RulesPage::drawOnWindow(sf::RenderWindow &window)
{
    window.draw(textRules);
    this->backButton->draw(window);
}

void RulesPage::checkOnEvent(sf::Event &event)
{
    this->backButton->checkOnEvent(event);
}

RulesPage::~RulesPage()
{
    delete this->backButton;
}
