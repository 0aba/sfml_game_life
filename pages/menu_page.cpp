#include "menu_page.hpp"
#include "Utils.hpp"

#include <iostream>

MenuPage::MenuPage(TypePage &pageView) : Page(pageView)
{
    this->pageView = pageView;

    if (!font.loadFromFile(FRONT_TEXT_PATH)) { return; }

    textPlay.setFont(font);
    textPlay.setString("Play");
    textPlay.setCharacterSize(24);
    textPlay.setFillColor(sf::Color::White);
    textPlay.setPosition(300, 100);

    textSettings.setFont(font);
    textSettings.setString("Settings");
    textSettings.setCharacterSize(24);
    textSettings.setFillColor(sf::Color::White);
    textSettings.setPosition(300, 200);

    textRules.setFont(font);
    textRules.setString("Rules");
    textRules.setCharacterSize(24);
    textRules.setFillColor(sf::Color::White);
    textRules.setPosition(300, 300);

    textExit.setFont(font);
    textExit.setString("Exit");
    textExit.setCharacterSize(24);
    textExit.setFillColor(sf::Color::White);
    textExit.setPosition(300, 400);
}

void MenuPage::drawOnWindow(sf::RenderWindow& window)
{

    window.draw(textPlay);
    window.draw(textSettings);
    window.draw(textRules);
    window.draw(textExit);
}

void MenuPage::checkOnEvent(sf::Event& event, sf::Vector2i mousePosition)
{
    // textPlay
    if (textPlay.getGlobalBounds().contains(static_cast<float>(mousePosition.x),
                                            static_cast<float>(mousePosition.y)))
    {
        textPlay.setFillColor(sf::Color::Green);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            pageView = TypePage::Game;
        }
    } else
    {
        textPlay.setFillColor(sf::Color::White);
    }
    // textSettings
    if (textSettings.getGlobalBounds().contains(static_cast<float>(mousePosition.x),
                                                static_cast<float>(mousePosition.y)))
    {
        textSettings.setFillColor(sf::Color::Green);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            pageView = TypePage::Settings;
        }
    } else
    {
        textSettings.setFillColor(sf::Color::White);
    }
    // textRules
    if (textRules.getGlobalBounds().contains(static_cast<float>(mousePosition.x),
                                             static_cast<float>(mousePosition.y)))
    {
        textRules.setFillColor(sf::Color::Green);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            pageView = TypePage::Rules;
        }
    } else
    {
        textRules.setFillColor(sf::Color::White);
    }
    // textExit
    if (textExit.getGlobalBounds().contains(static_cast<float>(mousePosition.x),
                                             static_cast<float>(mousePosition.y)))
    {
        textExit.setFillColor(sf::Color::Green);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            pageView = TypePage::Exit;
        }
    } else
    {
        textExit.setFillColor(sf::Color::White);
    }
}

void MenuPage::close(sf::RenderWindow& window)
{
    window.clear();
}
