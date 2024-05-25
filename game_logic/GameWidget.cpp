#include "GameWidget.hpp"


GameWidget::GameWidget(sf::RenderWindow* window,
                       sf::Vector2f size,
                       sf::Vector2f position,
                       Game* game,
                       unsigned short amountCellOnX,
                       unsigned short amountCellOnY)
{
    this->setWindow(*window);

    this->game = game;

    this->amountCellOnX = amountCellOnX;
    this->game->setArenaSizeX(amountCellOnX);
    this->amountCellOnY = amountCellOnY;
    this->game->setArenaSizeY(amountCellOnY);

    this->buttonGame = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (1, 1),
                                          sf::Vector2f (1, 1),
                                          nullptr,
                                          nullptr,
                                          "game button",
                                          this,
                                          GameWidget::clickButtonGame,
                                          sf::Color(50, 50, 50),
                                          sf::Color(100, 100, 100),
                                          sf::Color(150, 150, 150),
                                          sf::Color(200, 200, 200)
                                        );


    this->contextMenuCell = new my_gui::ContextMenu(*this->getWindow(),
                                                    sf::Vector2f (100, 100),
                                                    sf::Vector2f (1, 1),
                                                    nullptr
                                                    );

    this->sliderSpeed = new my_gui::HSlider(*this->getWindow(),
                                            sf::Vector2f (100, 25),
                                            sf::Vector2f (1, 1),
                                            nullptr,
                                            nullptr,
                                            nullptr,
                                            nullptr,
                                            .5f,
                                            this,
                                            [] (my_gui::OBJECT_GUI* contextCalled, my_gui::Slider* thisSlider) { /*None!!!*/ },
                                            sf::Color(50, 50, 50),
                                            sf::Color(100, 100, 100),
                                            sf::Color(150, 150, 150),
                                            sf::Color(200, 200, 200),
                                            GameWidget::MIN_SLIDER_VALUE,
                                            GameWidget::MAX_SLIDER_VALUE
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/dead_cell.png",
                                         nullptr,
                                         "dead cell",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::ContextMenuElement* thisElement) { GameWidget::changeCell(((GameWidget *) contextCalled), TypeCell::DeadCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/wall_cell.png",
                                         nullptr,
                                         "wall cell",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::ContextMenuElement* thisElement) { GameWidget::changeCell(((GameWidget *) contextCalled), TypeCell::Wall); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/killing_cell.png",
                                         nullptr,
                                         "killing cell",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::ContextMenuElement* thisElement) { GameWidget::changeCell(((GameWidget *) contextCalled), TypeCell::KillingCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/support_cell.png",
                                         nullptr,
                                         "support cell",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::ContextMenuElement* thisElement) { GameWidget::changeCell(((GameWidget *) contextCalled), TypeCell::LifeSupportCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );
    this->contextMenuCell->createElement(nullptr,
                                         "./resources_GUI/living_cell.png",
                                         nullptr,
                                         "live cell",
                                         this,
                                         [] (my_gui::OBJECT_GUI* contextCalled, my_gui::ContextMenuElement* thisElement) { GameWidget::changeCell(((GameWidget *) contextCalled), TypeCell::LivingCell); },
                                         sf::Color(50, 50, 50),
                                         sf::Color(100, 100, 100),
                                         sf::Color(150, 150, 150),
                                         sf::Color(200, 200, 200)
    );

    this->livingCell = new Cell(*this->getWindow(),
                                sf::Vector2f (1, 1),
                                sf::Vector2f (1, 1),
                                "./resources_GUI/living_cell.png"
                                );
    this->deadCell = new Cell(*this->getWindow(),
                              sf::Vector2f (1, 1),
                              sf::Vector2f (1, 1),
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

void GameWidget::clickButtonGame(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)
{
    if (((GameWidget*) contextCalled)->gameRunStatus)
    {
        ((GameWidget*) contextCalled)->runDeveloperLife->request_stop();
        ((my_gui::Button*) thisButton)->setText("run");

        ((GameWidget*) contextCalled)->gameRunStatus = false;
    }
    else /*if (!this->gameRunStatus)*/
    {
        ((GameWidget*) contextCalled)->runDeveloperLife = new std::jthread([contextCalled] (const std::stop_token& token) {
                    while (true)
                    {
                        if (token.stop_requested()) { return; }

                        std::this_thread::sleep_for(std::chrono::milliseconds (((GameWidget*) contextCalled)->sliderSpeed->getValuesPointer()));

                        ((GameWidget*) contextCalled)->game->developmentOfLife();
                    }
                });

        ((my_gui::Button*) thisButton)->setText("stop");
        ((GameWidget*) contextCalled)->gameRunStatus = true;
    }
}

void GameWidget::changeCell(GameWidget* gameWidget, TypeCell type) { gameWidget->game->setCell(gameWidget->selectedCellCoord, type); }

void GameWidget::setAmountCellOnX(unsigned short amount)
{
    this->amountCellOnX = amount;
    this->game->setArenaSizeX(amountCellOnX);
    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnX() const { return this->amountCellOnX; }

void GameWidget::setAmountCellOnY(unsigned short amount)
{
    this->amountCellOnY = amount;
    this->game->setArenaSizeY(amountCellOnY);
    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnY() const { return this->amountCellOnY; }

GameWidget::~GameWidget()
{
    delete this->buttonGame;
    delete this->sliderSpeed;
    delete this->contextMenuCell;

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
                                   (this->getSize().y * .8f) / this->amountCellOnY);

    this->livingCell->setSize(this->sizeCell);
    this->deadCell->setSize(this->sizeCell);
    this->wall->setSize(this->sizeCell);
    this->killingCell->setSize(this->sizeCell);
    this->lifeSupportCell->setSize(this->sizeCell);

    this->buttonGame->setSize(sf::Vector2f((this->getSize().x * .95f) / 2,
                                           this->getSize().y * .099f));
    this->sliderSpeed->setSize(sf::Vector2f((this->getSize().x * .95f) / 2,
                                            this->getSize().y * .099f));
    this->contextMenuCell->setSize(sf::Vector2f(this->getSize().x * .33f,
                                                this->getSize().y * .33f));
}

void GameWidget::setPosition(sf::Vector2f position)
{
    this->position = position;
    this->buttonGame->setPosition(sf::Vector2f(this->getPosition().x,
                                               this->getPosition().y +
                                               this->getSize().y -
                                               this->getSize().y * .099f));
    this->sliderSpeed->setPosition(sf::Vector2f(this->getPosition().x +
                                                this->getSize().x -
                                                (this->getSize().x * .95f) / 2,
                                                this->getPosition().y +
                                                this->getSize().y -
                                                this->getSize().y * .099f));
}

void GameWidget::setViewState(bool state) { this->viewState = state; }

void GameWidget::draw(sf::RenderWindow& window)
{
    if(!this->getViewState()) { return; }

    this->setWindow(window);

    for (int y = 0; y < this->amountCellOnY; ++y)
    {
        for (int x = 0; x < this->amountCellOnX; ++x)
        {
            TypeCell typeCurrentCell = this->game->getCell(Coords {(u16) x, (u16) y});

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

    if (this->selected) { this->contextMenuCell->draw(*this->getWindow()); }

    this->sliderSpeed->draw(*this->getWindow());
    this->buttonGame->draw(*this->getWindow());
}

void GameWidget::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    float x, y;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
    {
        this->selected = false;

        x = (sf::Mouse::getPosition(*this->getWindow()).x - this->getPosition().x) /
            this->sizeCell.x;
        y = (sf::Mouse::getPosition(*this->getWindow()).y - this->getPosition().y * .95f) /
            this->sizeCell.y;

        if (y >= 0 && y <= this->amountCellOnX
            &&
            x >= 0 && x <= this->amountCellOnY
            )
        {
            this->selected = true;
            this->selectedCellCoord = Coords {(u16) x, (u16) y};

            this->contextMenuCell->setPosition(sf::Vector2f (sf::Mouse::getPosition(*this->getWindow()).x,
                                                             sf::Mouse::getPosition(*this->getWindow()).y));
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed
             &&
             event.mouseButton.button == sf::Mouse::Left
             &&
            (this->contextMenuCell->getPosition().y > sf::Mouse::getPosition(*this->getWindow()).y
             ||
             this->contextMenuCell->getPosition().y + this->contextMenuCell->getSize().y < sf::Mouse::getPosition(*this->getWindow()).y
             ||
             this->contextMenuCell->getPosition().x > sf::Mouse::getPosition(*this->getWindow()).x
             ||
             this->contextMenuCell->getPosition().x + this->contextMenuCell->getSize().x < sf::Mouse::getPosition(*this->getWindow()).x
            ))
    {
        this->selected = false;
    }

    if (this->selected) { this->contextMenuCell->checkOnEvent(event); }

    this->sliderSpeed->checkOnEvent(event);
    this->buttonGame->checkOnEvent(event);
}



