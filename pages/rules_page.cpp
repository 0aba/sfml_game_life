#include "rules_page.hpp"


RulesPage::RulesPage(TypePage &pageView) : Page(pageView)
{
    this->pageView = pageView;

    if (!font.loadFromFile(FRONT_TEXT_PATH)) { return; }

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

    textBack.setFont(font);
    textBack.setString("Back to menu...");
    textBack.setCharacterSize(24);
    textBack.setFillColor(sf::Color::White);
    textBack.setPosition(50, 550);

}

void RulesPage::drawOnWindow(sf::RenderWindow &window)
{
    window.draw(textRules);
    window.draw(textBack);
}

void RulesPage::checkOnEvent(sf::Event &event, sf::Vector2i mousePosition)
{
    if (textBack.getGlobalBounds().contains(static_cast<float>(mousePosition.x),
                                            static_cast<float>(mousePosition.y)))
    {
        textBack.setFillColor(sf::Color::Green);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            pageView = TypePage::MenuPageType;
        }
    } else
    {
        textBack.setFillColor(sf::Color::White);
    }
}

void RulesPage::close(sf::RenderWindow &window)
{
    window.clear();
}