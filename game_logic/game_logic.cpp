#include <stdlib.h>
#include "game_logic.hpp"
#include "settings.hpp"


mapFilledCell __mapGame;



Coords getCoordAfterOffset(const Coords& CurrentCoords, const Offset& OffsetCoords)
{
    Coords ResultCoords;

    short resultOffsetX = (CurrentCoords.x + OffsetCoords.x) % __arenaSizeX;
    short resultOffsetY = (CurrentCoords.y + OffsetCoords.y) % __arenaSizeY;

    ResultCoords.x = resultOffsetX >= 0 ? resultOffsetX : __arenaSizeX + resultOffsetX;
    ResultCoords.y = resultOffsetY >= 0 ? resultOffsetY : __arenaSizeY + resultOffsetY;

    return ResultCoords;
}

TypeCell getNewTypeCell(const Coords& CoordsCell)
{
    TypeCell CurrentType = __mapGame.find(CoordsCell) != __mapGame.end()
                           ?
                           __mapGame.at(CoordsCell) : TypeCell::DeadCell;

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

    for (const Offset& OffsetNeighbor : displacementОptions)
    {
        if (OffsetNeighbor.x == 0 && OffsetNeighbor.y == 0) { continue; }

        Coords CoordsNeighbor = getCoordAfterOffset(CoordsCell, OffsetNeighbor);
        TypeCell NeighborType = __mapGame.find(CoordsNeighbor) != __mapGame.end()
                                ?
                                __mapGame.at(CoordsNeighbor) : TypeCell::DeadCell;

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


void developmentOfLife()
{
    mapFilledCell resultDevelopmentOfLife;

    for (auto& cell : __mapGame)
    {
        for (const Offset& optionOffset : displacementОptions)
        {
            Coords CooorsOption = getCoordAfterOffset(cell.first, optionOffset);
            TypeCell TypeOption = getNewTypeCell(CooorsOption);

            if (TypeOption == TypeCell::DeadCell) { continue; }

            resultDevelopmentOfLife[CooorsOption] = TypeOption;
        }
    }

    __mapGame = resultDevelopmentOfLife;
}

TypeCell getRandomCell()
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

void setRandomMapGame()
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