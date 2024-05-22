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
    this->size = size;

    this->sizeCell = sf::Vector2f (this->getSize().x / this->amountCellOnX,
                                   (this->getSize().y * .89f) / this->amountCellOnY);

    this->livingCell->setSize(this->sizeCell);
    this->deadCell->setSize(this->sizeCell);
    this->wall->setSize(this->sizeCell);
    this->killingCell->setSize(this->sizeCell);
    this->lifeSupportCell->setSize(this->sizeCell);

    this->buttonGame->setSize(sf::Vector2f((this->getSize().x * .95f) / 2,
                                           this->getSize().y * .099f));
    this->sliderSpeed->setSize(sf::Vector2f((this->getSize().x * .95f) / 2,
                                            this->getSize().y * .099f));
    this->contextMenuCell->setSize(sf::Vector2f(this->getSize().x * .15f,
                                                this->getSize().y * .15f));
}

void GameWidget::setPosition(sf::Vector2f position)
{
    this->buttonGame->setPosition(sf::Vector2f(this->getPosition().x,
                                               this->getPosition().y -
                                               this->getSize().y +
                                               this->getSize().y * .099f));
    this->sliderSpeed->setPosition(sf::Vector2f(this->getPosition().x +
                                                this->getSize().x -
                                                (this->getSize().x * .95f) / 2,
                                                this->getPosition().y -
                                                this->getSize().y +
                                                this->getSize().y * .099f));
}

void GameWidget::setViewState(bool state) { this->viewState = state; }

void GameWidget::draw(sf::RenderWindow &window)
{
    if(!this->getViewState()) { return; }

    for (int x = 0; x < this->amountCellOnY; ++x)
    {
        for (int y = 0; y < this->amountCellOnX; ++y)
        {
            TypeCell typeCurrentCell = this->game->getCell({(u16) y, (u16) x});

            Cell* viewCell;

            switch (typeCurrentCell)
            {
                case TypeCell::LivingCell: viewCell = this->livingCell; break;
                case TypeCell::DeadCell: viewCell = this->deadCell; break;
                case TypeCell::Wall: viewCell = this->wall; break;
                case TypeCell::KillingCell: viewCell = this->killingCell; break;
                case TypeCell::LifeSupportCell: viewCell = this->lifeSupportCell; break;
            }

            viewCell->setPosition(sf::Vector2f (this->getPosition().x + this->sizeCell.x * x,
                                            this->getPosition().y + this->sizeCell.y * y));
            viewCell->draw(*this->getWindow());
        }
    }

    this->sliderSpeed->draw(*this->getWindow());
    this->buttonGame->draw(*this->getWindow());
}

void GameWidget::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    float x, y;

    if (event.mouseButton.button == sf::Mouse::Right)
    {
        x = (sf::Mouse::getPosition(*this->getWindow()).x - this->getPosition().x) /
                this->amountCellOnX;
        y = (sf::Mouse::getPosition(*this->getWindow()).y - this->getPosition().y * .95f) /
                this->amountCellOnY;

        if (x >= 0 && x <= this->amountCellOnX
            &&
            y >= 0 && y <= this->amountCellOnY)
        {
            this->selected = true;
            this->selectedCellCoord = Coords {(u16) x, (u16) y};

            this->contextMenuCell->setPosition(sf::Vector2f (sf::Mouse::getPosition(*this->getWindow()).x,
                                                             sf::Mouse::getPosition(*this->getWindow()).y));
        }
        else /*if (x < 0 || x > this->amountCellOnX || y < 0 || y > this->amountCellOnY)*/
        {
            this->selected = false;
        }
    }

    if (this->selected) { this->contextMenuCell->draw(*this->getWindow()); }


    this->sliderSpeed->checkOnEvent(event);
    this->buttonGame->checkOnEvent(event);
}



