#include "Game.hpp"
#include <cstdlib>


Coords Game::getCoordAfterOffset(const Coords& CurrentCoords, const Offset& OffsetCoords)
{
    Coords ResultCoords;

    short resultOffsetX = (CurrentCoords.x + OffsetCoords.x) % this->_arenaSizeX;
    short resultOffsetY = (CurrentCoords.y + OffsetCoords.y) % this->_arenaSizeY;

    ResultCoords.x = resultOffsetX >= 0 ? resultOffsetX : this->_arenaSizeX + resultOffsetX;
    ResultCoords.y = resultOffsetY >= 0 ? resultOffsetY : this->_arenaSizeY + resultOffsetY;

    return ResultCoords;
}

TypeCell Game::getNewTypeCell(const Coords &CoordsCell)
{
    TypeCell CurrentType = this->_mapGame.find(CoordsCell) != this->_mapGame.end()
                           ?
                           this->_mapGame.at(CoordsCell) : TypeCell::DeadCell;

    switch (CurrentType)
    {
        case TypeCell::Wall:
            return TypeCell::Wall;
        case TypeCell::KillingCell:
            return TypeCell::KillingCell;
        case TypeCell::LifeSupportCell:
            return TypeCell::LifeSupportCell;
        default:
            break;
    }

    u16 amountLifeNeighbor = 0;
    bool neighborLifeSupport = false;
    bool neighborKilling = false;

    for (const Offset& OffsetNeighbor : displacementOptions)
    {
        if (OffsetNeighbor.x == 0 && OffsetNeighbor.y == 0) { continue; }

        Coords CoordsNeighbor = getCoordAfterOffset(CoordsCell, OffsetNeighbor);
        TypeCell NeighborType = this->_mapGame.find(CoordsNeighbor) != this->_mapGame.end()
                                ?
                                this->_mapGame.at(CoordsNeighbor) : TypeCell::DeadCell;

        switch (NeighborType)
        {
            case TypeCell::LivingCell:
                ++amountLifeNeighbor;
                break;
            case TypeCell::KillingCell:
                neighborKilling = true;
                break;
            case TypeCell::LifeSupportCell:
                neighborLifeSupport = true;
                break;
            default:
                break;
        }
    }

    if (neighborKilling)
    {
        return TypeCell::DeadCell;
    }
    else if (neighborLifeSupport && CurrentType == TypeCell::LivingCell)
    {
        return TypeCell::LivingCell;
    }
    else if (amountLifeNeighbor == 3 && CurrentType == TypeCell::DeadCell)
    {
        return TypeCell::LivingCell;
    }
    else if ((amountLifeNeighbor == 2 || amountLifeNeighbor == 3)
             &&
             CurrentType == TypeCell::LivingCell
            )
    {
        return TypeCell::LivingCell;
    }

    return TypeCell::DeadCell;
}

TypeCell Game::getRandomCell()
{
    if ((rand() % 100) <= _wallPercent)
    {
        return TypeCell::Wall;
    }
    else if ((rand() % 100) <= _killingPercent)
    {
        return TypeCell::KillingCell;
    }
    else if ((rand() % 100) <= _supportPercent)
    {
        return TypeCell::LifeSupportCell;
    }
    else if ((rand() % 100) <= _livingPercent)
    {
        return TypeCell::LivingCell;
    }

    return TypeCell::DeadCell;
}

void Game::setArenaSizeX(unsigned short size) { this->_arenaSizeX = size; }
u16 Game::getArenaSizeX() const { return this->_arenaSizeX; }

void Game::setArenaSizeY(unsigned short size) { this->_arenaSizeY = size; }
u16 Game::getArenaSizeY() const { return this->_arenaSizeY;}

void Game::setLivingPercent(unsigned short percent)
{
    if (MIN_VALUE_LIVING > percent || MAX_VALUE_LIVING < percent) { this->_livingPercent = DEFAULT_LIVING; }
    this->_livingPercent = percent;
}
u16 Game::getLivingPercent() const { return this->_livingPercent; }

void Game::setWallPercent(unsigned short percent)
{
    if (MIN_VALUE_SPECIAL_CELL > percent || MAX_VALUE_SPECIAL_CELL < percent) { this->_wallPercent = DEFAULT_SPECIAL_CELL; }
    this->_wallPercent = percent;
}
u16 Game::getWallPercent() const { return this->_wallPercent; }

void Game::setKillingPercent(unsigned short percent)
{
    if (MIN_VALUE_SPECIAL_CELL > percent || MAX_VALUE_SPECIAL_CELL < percent) { this->_killingPercent = DEFAULT_SPECIAL_CELL; }
    this->_killingPercent = percent;
}
u16 Game::getKillingPercent() const { return this->_killingPercent; }

void Game::setSupportPercent(unsigned short percent)
{
    if (MIN_VALUE_SPECIAL_CELL > percent || MAX_VALUE_SPECIAL_CELL < percent) { this->_supportPercent = DEFAULT_SPECIAL_CELL; }
    this->_supportPercent = percent;
}
u16 Game::getSupportPercent() const {return this->_supportPercent;}

void Game::developmentOfLife()
{
    mapFilledCell resultDevelopmentOfLife;

    for (auto& cell : _mapGame)
    {
        for (const Offset& optionOffset : displacementOptions)
        {
            Coords CooorsOption = getCoordAfterOffset(cell.first, optionOffset);
            TypeCell TypeOption = getNewTypeCell(CooorsOption);

            if (TypeOption == TypeCell::DeadCell) { continue; }

            resultDevelopmentOfLife[CooorsOption] = TypeOption;
        }
    }

    _mapGame = resultDevelopmentOfLife;
}

void Game::setCell(Coords coord, TypeCell type) { this->_mapGame[coord] = type; }

TypeCell Game::getCell(Coords coord) { return this->_mapGame.find(coord) != this->_mapGame.end()
                                              ?
                                              this->_mapGame.at(coord) : TypeCell::DeadCell;}

void Game::setRandomMapGame()
{
    TypeCell typeCurrentCell;
    for (u16 x = 0; x < _arenaSizeX; ++x)
    {
        for (u16 y = 0; y < _arenaSizeY; ++y)
        {
            typeCurrentCell = getRandomCell();

            if (typeCurrentCell == TypeCell::DeadCell) { continue; }

            _mapGame[{ x, y }] = typeCurrentCell;
        }
    }
}

void Game::clearMapGame() {  this->_mapGame.clear(); }

mapFilledCell Game::getMapGame() const { return this->_mapGame; }


