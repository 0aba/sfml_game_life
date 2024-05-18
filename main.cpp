#include <iostream> // todo! del
#include <SFML/Graphics.hpp>
#include "./pages/menu_page.hpp" // todo! change
#include "./pages/rules_page.hpp" // todo! change
#include "./pages/settings_page.hpp" // todo! change
#include "./pages/game_page.hpp." // todo! change

#include "GUI/MultilineTextArea.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "game life");

    sf::Font font; //todo! test
    font.loadFromFile(FRONT_TEXT_PATH); //todo! test

/*sf::Text te ("Adw;,dpw_25132A", font, 30);
1) длинаю.х / te.getGlobalBounds().width / te.getString().getSize() = длина символа в ширену
2) te.getString().getSize() /  длина символа в ширену = строк


 строка строка = "";

 ++строка

 и условие

 ---

// Теперь переменная symbolWidth содержит ширину символа "A" в пикселях
 */
    //float w = te.getGlobalBounds().width / te.getString().getSize();

    sf::Vector2f s = sf::Vector2f(400  , 400);
    sf::Vector2f p = sf::Vector2f(5, 5);

    sf::RectangleShape r;
    r.setSize(s);
    r.setPosition(p);


    my_gui::MultilineTextArea multilineTextArea (window,
                                                 s,
                                                 p,
                                                 nullptr,
                                                 sf::Color(255,155,55),
                                                 "kojj  efi   eefjefciwejcfk 1111eee,,,,,3,d,2c,,,,d12d//" // ........_WW3QQ111WW
    );

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
        window.draw(r);
        multilineTextArea.draw(window);


        window.display();

        viewPage->close(window);
    }


    return EXIT_SUCCESS;
}