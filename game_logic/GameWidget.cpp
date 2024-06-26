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

    this->buttonRandom = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (1, 1),
                                          sf::Vector2f (1, 1),
                                          nullptr,
                                          nullptr,
                                          "random",
                                          this,
                                          GameWidget::clickButtonRandom,
                                          sf::Color(50, 50, 50),
                                          sf::Color(100, 100, 100),
                                          sf::Color(150, 150, 150),
                                          sf::Color(200, 200, 200)
                                          );

    this->buttonClear = new my_gui::Button(*this->getWindow(),
                                          sf::Vector2f (1, 1),
                                          sf::Vector2f (1, 1),
                                          nullptr,
                                          nullptr,
                                          "clear",
                                          this,
                                          GameWidget::clickButtonClear,
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
                                         (char *) "./resources_GUI/dead_cell.png",
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
                                         (char *) "./resources_GUI/wall_cell.png",
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
                                         (char *) "./resources_GUI/killing_cell.png",
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
                                         (char *) "./resources_GUI/support_cell.png",
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
                                         (char *) "./resources_GUI/living_cell.png",
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
                                (char *) "./resources_GUI/living_cell.png"
                                );
    this->deadCell = new Cell(*this->getWindow(),
                              sf::Vector2f (1, 1),
                              sf::Vector2f (1, 1),
                              (char *) "./resources_GUI/dead_cell.png"
                              );
    this->wall = new Cell(*this->getWindow(),
                          sf::Vector2f (0, 0),
                          sf::Vector2f (0, 0),
                          (char *) "./resources_GUI/wall_cell.png"
                          );
    this->killingCell = new Cell(*this->getWindow(),
                                 sf::Vector2f (0, 0),
                                 sf::Vector2f (0, 0),
                                 (char *) "./resources_GUI/killing_cell.png"
                                 );
    this->lifeSupportCell = new Cell(*this->getWindow(),
                                     sf::Vector2f (0, 0),
                                     sf::Vector2f (0, 0),
                                     (char *) "./resources_GUI/support_cell.png"
                                     );

    ((GameWidget*) this)->setSize(size);
    ((GameWidget*) this)->setPosition(position);

}

void GameWidget::clickButtonGame(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)
{
    if (((GameWidget*) contextCalled)->gameRunStatus)
    {
        ((GameWidget*) contextCalled)->runDeveloperLife->request_stop();
        ((GameWidget*) contextCalled)->runDeveloperLife->join();

        ((my_gui::Button*) thisButton)->setText("run");

        ((GameWidget*) contextCalled)->gameRunStatus = false;
    }
    else /*if (!this->gameRunStatus)*/
    {
        ((GameWidget*) contextCalled)->runDeveloperLife = new std::jthread([] (const std::stop_token& token, my_gui::OBJECT_GUI& contextCalled) {
            while (true)
            {
                if (token.stop_requested()) { return; }

                std::this_thread::sleep_for(std::chrono::milliseconds (((GameWidget&) contextCalled).sliderSpeed->getValuesPointer()));

                ((GameWidget&) contextCalled).gameMutex.lock();
                ((GameWidget&) contextCalled).game->developmentOfLife();
                ((GameWidget&) contextCalled).gameMutex.unlock();
            }
        }, std::ref(*contextCalled));

        ((my_gui::Button*) thisButton)->setText("stop");
        ((GameWidget*) contextCalled)->gameRunStatus = true;
    }
}

void GameWidget::clickButtonRandom(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)
{
    ((GameWidget*) contextCalled)->gameMutex.lock();
    ((GameWidget*) contextCalled)->game->clearMapGame();
    ((GameWidget*) contextCalled)->game->setRandomMapGame();
    ((GameWidget*) contextCalled)->gameMutex.unlock();
}

void GameWidget::clickButtonClear(my_gui::OBJECT_GUI* contextCalled, my_gui::Button* thisButton)
{
    ((GameWidget*) contextCalled)->gameMutex.lock();
    ((GameWidget*) contextCalled)->game->clearMapGame();
    ((GameWidget*) contextCalled)->gameMutex.unlock();
}

void GameWidget::changeCell(GameWidget* gameWidget, TypeCell type)
{
    gameWidget->gameMutex.lock();
    gameWidget->game->setCell(gameWidget->selectedCellCoord, type);
    gameWidget->gameMutex.unlock();
}

void GameWidget::setAmountCellOnX(unsigned short amount)
{
    this->amountCellOnX = amount;
    this->game->setArenaSizeX(amount);
    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnX() const { return this->amountCellOnX; }

void GameWidget::setAmountCellOnY(unsigned short amount)
{
    this->amountCellOnY = amount;
    this->game->setArenaSizeY(amount);
    this->setSize(this->getSize());
}

u16 GameWidget::getAmountCellOnY() const { return this->amountCellOnY; }

void GameWidget::setLivingPercent(unsigned short percent) { this->game->setLivingPercent(percent); }

u16 GameWidget::getLivingPercent() const { return this->game->getLivingPercent(); }

void GameWidget::setWallPercent(unsigned short percent) { this->game->setWallPercent(percent); }

u16 GameWidget::getWallPercent() const { return this->game->getWallPercent(); }

void GameWidget::setKillingPercent(unsigned short percent) { this->game->setKillingPercent(percent); }

u16 GameWidget::getKillingPercent() const { return this->game->getKillingPercent(); }

void GameWidget::setSupportPercent(unsigned short percent) { this->game->setSupportPercent(percent); }

u16 GameWidget::getSupportPercent() const { return this->game->getSupportPercent(); }

GameWidget::~GameWidget()
{
    delete this->buttonGame;
    delete this->buttonClear;
    delete this->buttonRandom;
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

    this->buttonGame->setSize(sf::Vector2f((this->getSize().x * .95f) / 6,
                                           this->getSize().y * .099f));
    this->buttonRandom->setSize(sf::Vector2f((this->getSize().x * .95f) / 6,
                                           this->getSize().y * .099f));
    this->buttonClear->setSize(sf::Vector2f((this->getSize().x * .95f) / 6,
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
    this->buttonRandom->setPosition(sf::Vector2f(this->getPosition().x +
                                               (this->getSize().x * .95f) / 6,
                                               this->getPosition().y +
                                               this->getSize().y -
                                               this->getSize().y * .099f));
    this->buttonClear->setPosition(sf::Vector2f(this->getPosition().x +
                                                 (this->getSize().x * .95f) / 3,
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

    this->gameMutex.lock();
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
    this->gameMutex.unlock();

    if (this->selected) { this->contextMenuCell->draw(*this->getWindow()); }

    this->sliderSpeed->draw(*this->getWindow());
    this->buttonGame->draw(*this->getWindow());
    this->buttonRandom->draw(*this->getWindow());
    this->buttonClear->draw(*this->getWindow());
}

void GameWidget::checkOnEvent(sf::Event event)
{
    if(!this->getViewState()) { return; }

    float x = (sf::Mouse::getPosition(*this->getWindow()).x - this->getPosition().x) /
        this->sizeCell.x;
    float y = (sf::Mouse::getPosition(*this->getWindow()).y - this->getPosition().y * .95f) /
        this->sizeCell.y;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
    {
        this->selected = false;

        this->selectedCellCoord = Coords {(u16) x, (u16) y};

        if (y >= 0 && y <= this->amountCellOnY
            &&
            x >= 0 && x <= this->amountCellOnX
            )
        {
            this->selected = true;

            this->contextMenuCell->setPosition(sf::Vector2f (sf::Mouse::getPosition(*this->getWindow()).x,
                                                             sf::Mouse::getPosition(*this->getWindow()).y));
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed
             &&
             event.mouseButton.button == sf::Mouse::Left
            )
    {
        if (y >= 0 && y <= this->amountCellOnY
            &&
            x >= 0 && x <= this->amountCellOnX
            &&
            (this->contextMenuCell->getPosition().y > sf::Mouse::getPosition(*this->getWindow()).y
             ||
             this->contextMenuCell->getPosition().y + this->contextMenuCell->getSize().y < sf::Mouse::getPosition(*this->getWindow()).y
             ||
             this->contextMenuCell->getPosition().x > sf::Mouse::getPosition(*this->getWindow()).x
             ||
             this->contextMenuCell->getPosition().x + this->contextMenuCell->getSize().x < sf::Mouse::getPosition(*this->getWindow()).x
             ||
             !this->selected
            ))
        {
            this->selected = false;

            this->selectedCellCoord = Coords {(u16) x, (u16) y};

            TypeCell currentType = this->game->getCell(selectedCellCoord);

            if (currentType == TypeCell::LivingCell) { this->game->setCell(selectedCellCoord, TypeCell::DeadCell); }
            else if (currentType == TypeCell::DeadCell) { this->game->setCell(selectedCellCoord, TypeCell::LivingCell); }

        }
    }

    if (this->selected) { this->contextMenuCell->checkOnEvent(event); }

    this->sliderSpeed->checkOnEvent(event);
    this->buttonGame->checkOnEvent(event);
    this->buttonRandom->checkOnEvent(event);
    this->buttonClear->checkOnEvent(event);
}

void GameWidget::breakGame()
{
    if (this->gameRunStatus) { GameWidget::clickButtonGame(this, this->buttonGame); }
}
