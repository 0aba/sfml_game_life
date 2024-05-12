#include <iostream> // todo! del
#include <SFML/Graphics.hpp>
#include "./pages/menu_page.hpp" // todo! change
#include "./pages/rules_page.hpp" // todo! change
#include "./pages/settings_page.hpp" // todo! change
#include "./pages/game_page.hpp." // todo! change

#include "GUI/Button.hpp" // todo! test
#include "GUI/HSlider.hpp"  // todo! test
#include "GUI/ContextMenu.hpp"  // todo! test
#include "GUI/ContextMenuElement.hpp"  // todo! test
#include "GUI/Widget.hpp"  // todo! test


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "game life");

    sf::Font font; //todo! test
    font.loadFromFile(FRONT_TEXT_PATH); //todo! test


    my_gui::Button button
                    (window,
                     sf::Vector2f(100, 50),
                   sf::Vector2f(50, 50),
                   nullptr,
                   nullptr,
                   "button",
                   *([](sf::RenderWindow* window, my_gui::Widget* widget)
                   {
                       ((my_gui::Button*)widget)->setViewState(false);
                   }),
                   sf::Color(255, 219, 200),
                   sf::Color(110, 110, 110, 105),
                   sf::Color(151, 197, 139, 64),
                   sf::Color(98, 97, 160, 128)
            ); //todo! test

    my_gui::HSlider hSlider(window,
                    sf::Vector2f(250, 25),
                    sf::Vector2f(100, 200),
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr,
                    .5f,
                    *([](sf::RenderWindow* window, my_gui::Widget* widget)
                    {
                        std::cout << "val: " << ((my_gui::HSlider*)widget)->getValuesPointer() << std::endl;
                    }),
                    sf::Color(0, 255, 0),
                    sf::Color(110, 110, 110, 105),
                    sf::Color(151, 197, 139, 64),
                    sf::Color(98, 97, 160, 128),
                    0,
                    10
                    ); //todo! test

    my_gui::ContextMenuElement contextMenuElement(window,
                                                  sf::Vector2f(100, 50),
                                                  sf::Vector2f(300, 50),
                                                  nullptr,
                                                  nullptr,
                                                  nullptr,
                                                  "element",
                                                  *([](sf::RenderWindow* window, my_gui::Widget* widget)
                                                  {
                                                      std::cout << "click on elemet" << std::endl;
                                                  }),
                                                  sf::Color(255, 219, 200),
                                                  sf::Color(110, 110, 110, 105),
                                                  sf::Color(151, 197, 139, 64),
                                                  sf::Color(98, 97, 160, 128)
                                                  ); // todo!


    my_gui::ContextMenu contextMenu (window,
                                     sf::Vector2f(100, 300),
                                     sf::Vector2f(100, 50),
                                     nullptr,
                                     10
                                     );

    std::cout << contextMenu.createDefaultElement();
    contextMenu.addElement(&contextMenuElement);
    std::cout << contextMenu.createDefaultElement();
    std::cout << contextMenu.createDefaultElement();
    std::cout << contextMenu.createDefaultElement();

    contextMenu.setMaxAmountElements(2);
    contextMenu.delElementAt(1);

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

            //button.checkOnEvent(event); //todo! test
            //hSlider.checkOnEvent(event); //todo! test
            contextMenu.checkOnEvent(event); //todo! test
            //contextMenu.getElementAt(0)->checkOnEvent(event);
        }

        viewPage->drawOnWindow(window);
        //button.draw(window); //todo! test
        //hSlider.draw(window); //todo! test
        contextMenu.draw(window); //todo! test
        //contextMenu.getElementAt(0)->draw(window);

        window.display();

        viewPage->close(window);
    }

    contextMenu.freeMemoryWidget(); // todo! test

    return EXIT_SUCCESS;
}