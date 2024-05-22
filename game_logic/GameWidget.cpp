#include "GameWidget.hpp"



GameWidget::GameWidget(sf::RenderWindow* window,
                       sf::Vector2f size,
                       sf::Vector2f position,
                       unsigned short amountCellOnX,
                       unsigned short amountCellOnY)
{
    this->setWindow(*window);

    this->amountCellOnX = amountCellOnX; //this->setAmountCellOnX(amountCellOnX);
    this->amountCellOnY = amountCellOnY; //this->setAmountCellOnY(amountCellOnY);

    this->buttonGame = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (0, 0),
                                          sf::Vector2f (0, 0),
                                          nullptr,
                                          nullptr,
                                          "run",
                                          [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget*) widget)->clickButtonGame(window, widget);},
                                          sf::Color(50, 50, 50),
                                          sf::Color(100, 100, 100),
                                          sf::Color(150, 150, 150),
                                          sf::Color(200, 200, 200)
                                        );

    this->sliderSpeed = new my_gui::HSlider(*this->getWindow(),
                                            sf::Vector2f (0, 0),
                                            sf::Vector2f (0, 0),
                                            nullptr,
                                            nullptr,
                                            nullptr,
                                            nullptr,
                                            .5f,
                                            [] (sf::RenderWindow* window, Widget* widget) { /*None!!!*/ },
                                            sf::Color(50, 50, 50),
                                            sf::Color(100, 100, 100),
                                            sf::Color(150, 150, 150),
                                            sf::Color(200, 200, 200),
                                            GameWidget::MIN_SLIDER_VALUE,
                                            GameWidget::MAX_SLIDER_VALUE
                                            );

    this->contextMenuCell = new my_gui::ContextMenu(*this->getWindow(),
                                                    sf::Vector2f (0, 0),
                                                    sf::Vector2f (0, 0),
                                                    nullptr
                                                    );

    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/living_cell.png",
                                         nullptr,
                                         "live cell",
                                         [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget *) widget)->changeCell(TypeCell::LivingCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
                                         );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/dead_cell.png",
                                         nullptr,
                                         "dead cell",
                                         [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget *) widget)->changeCell(TypeCell::DeadCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/wall_cell.png",
                                         nullptr,
                                         "wall cell",
                                         [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget *) widget)->changeCell(TypeCell::Wall); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/killing_cell.png",
                                         nullptr,
                                         "killing cell",
                                         [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget *) widget)->changeCell(TypeCell::KillingCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/support_cell.png",
                                         nullptr,
                                         "support cell",
                                         [] (sf::RenderWindow* window, Widget* widget) { ((GameWidget *) widget)->changeCell(TypeCell::LifeSupportCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );

    this->livingCell = new Cell(*this->getWindow(),
                                sf::Vector2f (0, 0),
                                sf::Vector2f (0, 0),
                                "./resources_GUI/living_cell.png"
                                );
    this->deadCell = new Cell(*this->getWindow(),
                              sf::Vector2f (0, 0),
                              sf::Vector2f (0, 0),
                              "./resources_GUI/dead_cell.png"
                              );
    this->wall = new Cell(*this->getWindow(),
                          sf::Vector2f (0, 0),
                          sf::Vector2f (0, 0),
                          "./resources_GUI/wall_cell.png"
                          );
    this->killingCell = new Cell(*this->getWindow(),
                                 sf::Vector2f (0, 0),
                                 sf::Vector2f (0, 0),
                                 "./resources_GUI/killing_cell.png"
                                 );
    this->lifeSupportCell = new Cell(*this->getWindow(),
                                     sf::Vector2f (0, 0),
                                     sf::Vector2f (0, 0),
                                     "./resources_GUI/support_cell.png"
                                     );

    ((GameWidget*) this)->setSize(size);
    ((GameWidget*) this)->setPosition(position);
}

void GameWidget::clickButtonGame(sf::RenderWindow* window, Widget* widget)
{
    if (this->gameRunStatus)
    {
        this->runDeveloperLife = new std::jthread(
                [this] (const std::stop_token& token) {
                    while (true)
                    {
                        if (token.stop_requested()) { return; }

                        std::this_thread::sleep_for(std::chrono::seconds (this->sliderSpeed->getValuesPointer()));

                        this->game->developmentOfLife();
                    }
                });

        this->buttonGame->setText("run");
        this->gameRunStatus = false;
    }
    else /*if (!this->gameRunStatus)*/
    {
        this->runDeveloperLife->request_stop();
        this->buttonGame->setText("stop");
        this->gameRunStatus = true;
    }
}

void GameWidget::changeCell(TypeCell type) { this->game->setCell(this->selectedCellCoord, type); }

void GameWidget::setAmountCellOnX(unsigned short amount)
{
    this->amountCellOnX = amount;

    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnX() const { return this->amountCellOnX; }

void GameWidget::setAmountCellOnY(unsigned short amount)
{
    this->amountCellOnY = amount;

    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnY() const { return this->amountCellOnY; }

GameWidget::~GameWidget()
{
    delete this->buttonGame;
    delete this->sliderSpeed;
    delete this->contextMenuCell;
    delete this->game;

    delete this->livingCell;
    delete this->deadCell;
    delete this->wall;
    delete this->killingCell;
    delete this->lifeSupportCell;
}

void GameWidget::setSize(sf::Vector2f size)
{

}

void GameWidget::setPosition(sf::Vector2f position)
{

}

void GameWidget::setViewState(bool state) { this->viewState = state; }

void GameWidget::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }


}

void GameWidget::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }


}



