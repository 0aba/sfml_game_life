#include <iostream> // todo! del
#include <SFML/Graphics.hpp>
#include "./pages/menu_page.hpp" // todo! change
#include "./pages/rules_page.hpp" // todo! change
#include "./pages/settings_page.hpp" // todo! change
#include "./pages/game_page.hpp." // todo! change

//#include "GUI/ContextMenu.hpp"
#include "GUI/ContextMenuElement.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "game life");

    sf::Font font; //todo! test
    font.loadFromFile(FRONT_TEXT_PATH); //todo! test


    sf::Vector2i mousePosition;

    TypePage pageViewChange = TypePage::Menu;
    Page* viewPage;
    MenuPage menuPage(pageViewChange);
    GamePage gamePage(pageViewChange);
    SettingsPage settingsPage(pageViewChange);
    RulesPage rulesPage(pageViewChange);

    while (window.isOpen())
    {
        switch (pageViewChange)
        {
            case Menu: viewPage = &menuPage; break;
            case Game: viewPage = &gamePage; break;
            case Settings: viewPage = &settingsPage; break;
            case Rules: viewPage = &rulesPage; break;
            case Exit: return EXIT_SUCCESS;
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
        }

        viewPage->drawOnWindow(window);

        window.display();

        viewPage->close(window);
    }


    return EXIT_SUCCESS;
}