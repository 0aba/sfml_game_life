#include "settings_page.hpp"


SettingsPage::SettingsPage(TypePage &pageView) : Page(pageView)
{
    this->pageView = pageView;

    if (!font.loadFromFile(FRONT_TEXT_PATH)) { return; }

    textBack.setFont(font);
    textBack.setString("Back to menu...");
    textBack.setCharacterSize(24);
    textBack.setFillColor(sf::Color::White);
    textBack.setPosition(50, 550);
}


void SettingsPage::drawOnWindow(sf::RenderWindow& window)
{
    window.draw(textBack);
}

void SettingsPage::checkOnEvent(sf::Event& event, sf::Vector2i mousePosition)
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

void SettingsPage::close(sf::RenderWindow& window)
{
    window.clear();
}