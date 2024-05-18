#include "Game.hpp"
#include <stdlib.h>


Coords Game::getCoordAfterOffset(const Coords &CurrentCoords, const Offset &OffsetCoords)
{
    Coords ResultCoords;

    short resultOffsetX = (CurrentCoords.x + OffsetCoords.x) % this->__arenaSizeX;
    short resultOffsetY = (CurrentCoords.y + OffsetCoords.y) % this->__arenaSizeY;

    ResultCoords.x = resultOffsetX >= 0 ? resultOffsetX : this->__arenaSizeX + resultOffsetX;
    ResultCoords.y = resultOffsetY >= 0 ? resultOffsetY : this->__arenaSizeY + resultOffsetY;

    return ResultCoords;
}

TypeCell Game::getNewTypeCell(const Coords &CoordsCell)
{
    TypeCell CurrentType = this->__mapGame.find(CoordsCell) != this->__mapGame.end()
                           ?
                           this->__mapGame.at(CoordsCell) : TypeCell::DeadCell;

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
        TypeCell NeighborType = this->__mapGame.find(CoordsNeighbor) != this->__mapGame.end()
                                ?
                                this->__mapGame.at(CoordsNeighbor) : TypeCell::DeadCell;

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
    if ((rand() % 100) <= __WallPercent)
    {
        return TypeCell::Wall;
    }
    else if ((rand() % 100) <= __KillingPercent)
    {
        return TypeCell::KillingCell;
    }
    else if ((rand() % 100) <= __SupportPercent)
    {
        return TypeCell::LifeSupportCell;
    }
    else if ((rand() % 100) <= __LivingPercent)
    {
        return TypeCell::LivingCell;
    }

    return TypeCell::DeadCell;
}

void Game::setArenaSizeX(unsigned short size) { this->__arenaSizeX = size; }
u16 Game::getArenaSizeX() const { return this->__arenaSizeX; }

void Game::setArenaSizeY(unsigned short size) { this->__arenaSizeY = size; }
u16 Game::getArenaSizeY() const { return this->__arenaSizeY;}

void Game::setTimeStep(unsigned short timeStep) { this->__timeStep = timeStep; }
u16 Game::getTimeStep() const { return this->__timeStep;}

void Game::setAmountIterations(unsigned short iterations) { this->__amountIterations = iterations; }
u16 Game::getAmountIterations() const { return this->__amountIterations; }

void Game::setLivingPercent(unsigned short percent) { this->__LivingPercent = percent; }
u16 Game::getLivingPercent() const { return this->__LivingPercent; }

void Game::setWallPercent(unsigned short percent) { this->__WallPercent = percent; }
u16 Game::getWallPercent() const { return this->__WallPercent; }

void Game::setKillingPercent(unsigned short percent) { this->__KillingPercent = percent; }
u16 Game::getKillingPercent() const { return this->__KillingPercent; }

void Game::setSupportPercent(unsigned short percent) { this->__SupportPercent = percent; }
u16 Game::getSupportPercent() const {return this->__SupportPercent;}

void Game::developmentOfLife()
{
    mapFilledCell resultDevelopmentOfLife;

    for (auto& cell : __mapGame)
    {
        for (const Offset& optionOffset : displacementOptions)
        {
            Coords CooorsOption = getCoordAfterOffset(cell.first, optionOffset);
            TypeCell TypeOption = getNewTypeCell(CooorsOption);

            if (TypeOption == TypeCell::DeadCell) { continue; }

            resultDevelopmentOfLife[CooorsOption] = TypeOption;
        }
    }

    __mapGame = resultDevelopmentOfLife;
}
void Game::setRandomMapGame()
{
    TypeCell typeCurrentCell;
    for (u16 x = 0; x < __arenaSizeX; ++x)
    {
        for (u16 y = 0; y < __arenaSizeY; ++y)
        {
            typeCurrentCell = getRandomCell();

            if (typeCurrentCell == TypeCell::DeadCell) { continue; }

            __mapGame[{ x, y }] = typeCurrentCell;
        }
    }
}

mapFilledCell Game::getMapGame() const { return this->__mapGame; }
