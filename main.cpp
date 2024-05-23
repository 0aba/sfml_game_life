#include <iostream> // todo! del
#include <SFML/Graphics.hpp>
#include "./pages/menu_page.hpp" // todo! change
#include "./pages/rules_page.hpp" // todo! change
#include "./pages/settings_page.hpp" // todo! change
#include "./pages/game_page.hpp" // todo! change

#include "game_logic/GameWidget.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "game life");

    sf::Font font; //todo! test
    font.loadFromFile(FRONT_TEXT_PATH); //todo! test

    sf::Vector2f s (600, 400);
    sf::Vector2f p (50, 40);
    //sf::RectangleShape bg;
    //bg.setSize(s);
   // bg.setPosition(p);



    GameWidget g = GameWidget(&window,
             s,
             p,
             10,
             10);

    sf::Vector2i mousePosition;

    TypePage pageViewChange = TypePage::MenuPageType;
    Page* viewPage;
    MenuPage menuPage(pageViewChange);
    GamePage gamePage(pageViewChange);
    SettingsPage settingsPage(pageViewChange);
    RulesPage rulesPage(pageViewChange);

    while (window.isOpen())
    {
        switch (pageViewChange)
        {
            case MenuPageType: viewPage = &menuPage; break;
            case GamePageType: viewPage = &gamePage; break;
            case SettingsPageType: viewPage = &settingsPage; break;
            case RulesPageType: viewPage = &rulesPage; break;
            case ExitPageType: return EXIT_SUCCESS;
        }

        sf::Event event;
        
        mousePosition = sf::Mouse::getPosition(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            viewPage->checkOnEvent(event, mousePosition);
            g.checkOnEvent(event);
        }

        viewPage->drawOnWindow(window);
        g.draw(window);

        window.display();

        viewPage->close(window);
    }


    return EXIT_SUCCESS;
}