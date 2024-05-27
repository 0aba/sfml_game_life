#include <SFML/Graphics.hpp>
#include "./pages/MenuPage.hpp"
#include "./pages/RulesPage.hpp"
#include "./pages/SettingsPage.hpp"
#include "./pages/GamePage.hpp"

#include "game_logic/Game.hpp"

//////
#include <iostream>
#include "./GUI/MultilineTextArea.hpp"
int main()
{
     sf::RenderWindow window(sf::VideoMode(800, 700), "game life");

    Game* game = new Game();

    TypePage pageViewChange = TypePage::MenuPageType;
    Page* viewPage;
    MenuPage menuPage(&window, &pageViewChange);
    GamePage gamePage(&window, &pageViewChange, game);
    SettingsPage settingsPage(&window, &pageViewChange, gamePage.getPtrOnGameWidget());
    RulesPage rulesPage(&window, &pageViewChange);

    while (window.isOpen())
    {
        switch (pageViewChange)
        {
            case MenuPageType: viewPage = &menuPage; break;
            case GamePageType: viewPage = &gamePage; break;
            case SettingsPageType: viewPage = &settingsPage; break;
            case RulesPageType: viewPage = &rulesPage; break;
            case ExitPageType: window.close();
        }

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            viewPage->checkOnEvent(event);
        }

        viewPage->drawOnWindow(window);

        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}