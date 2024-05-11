#ifndef GAME_LIFE_GAME_LOGIC_HPP
#define GAME_LIFE_GAME_LOGIC_HPP

#include "./my_types.hpp"


struct Offset {
    i16 x = 0;
    i16 y = 0;
};

#define AMOUNT_DISPLACEMENT_ОPTIONS 9

const Offset displacementОptions[AMOUNT_DISPLACEMENT_ОPTIONS] =
        {
                {-1,  1}, {0,  1}, {1,  1},
                {-1,  0}, {0,  0}, {1,  0},
                {-1, -1}, {0, -1}, {1, -1}
        };

struct   Coords {
    u16 x = 0;
    u16 y = 0;

    bool operator==(const Coords& otherCoords) const
    {
        return (otherCoords.x == this->x)
               &&
               (otherCoords.y == this->y);
    }

    u32 operator()(const Coords& сoords) const
    {
        /*  Решение возможной колизии, повысить значимось имерения на N, где N не является 0 или 1 и в моем случае > 0. */
#define SIGNIFICANCE_COORDS_X 2

        return SIGNIFICANCE_COORDS_X * сoords.x + сoords.y;
    }

};

enum     TypeCell {
    LivingCell      = '#',
    DeadCell        = '_',
    Wall            = 'W',
    KillingCell     = 'K',
    LifeSupportCell = 'S'
};

extern mapFilledCell __mapGame;

Coords   getCoordAfterOffset(const Coords& CurrentCoords, const Offset& OffsetCoords);

TypeCell getNewTypeCell(const Coords& CoordsCell);

void     developmentOfLife();

void     setRandomMapGame();

TypeCell getRandomCell();

#endif //GAME_LIFE_GAME_LOGIC_HPP
