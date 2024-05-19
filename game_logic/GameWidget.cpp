#include "GameWidget.hpp"


GameWidget::GameWidget(sf::Vector2f size,
                       sf::Vector2f position,
                       unsigned short amountCellOnX,
                       unsigned short amountCellOnY)
{

}

void GameWidget::gameRuning(std::stop_token token)
{

}

void GameWidget::onChangeSliderSpeed()
{

}

void GameWidget::onChangeCell(TypeCell type)
{

}

void GameWidget::updateArena()
{

}

void GameWidget::setAmountCellOnX(unsigned short amount)
{

}
u16 GameWidget::getAmountCellOnX() const { return this->amountCellOnX; }

void GameWidget::setAmountCellOnY(unsigned short amount)
{

}
u16 GameWidget::getAmountCellOnY() const { return this->amountCellOnY; }

GameWidget::~GameWidget()
{
    delete this->buttonGame;
    delete this->sliderSpeed;
    delete this->contextMenuCell;
}

